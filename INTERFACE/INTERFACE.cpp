#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QtSql>
#include <QDebug>

class MainWindow : public QWidget {
public:
    MainWindow(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("Base de Datos");

        QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);

        // Widgets para buscar
        QHBoxLayout *layoutBuscar = new QHBoxLayout();
        QLabel *labelBuscar = new QLabel("Buscar Nombre:");
        entryBuscar = new QLineEdit();
        QPushButton *btnBuscar = new QPushButton("Buscar");
        layoutBuscar->addWidget(labelBuscar);
        layoutBuscar->addWidget(entryBuscar);
        layoutBuscar->addWidget(btnBuscar);
        layoutPrincipal->addLayout(layoutBuscar);

        // Widgets para ingresar datos
        QHBoxLayout *layoutIngresar = new QHBoxLayout();
        QLabel *labelNombre = new QLabel("Nombre:");
        entryNombre = new QLineEdit();
        QLabel *labelEdad = new QLabel("Edad:");
        entryEdad = new QLineEdit();
        QPushButton *btnIngresar = new QPushButton("Ingresar Datos");
        layoutIngresar->addWidget(labelNombre);
        layoutIngresar->addWidget(entryNombre);
        layoutIngresar->addWidget(labelEdad);
        layoutIngresar->addWidget(entryEdad);
        layoutIngresar->addWidget(btnIngresar);
        layoutPrincipal->addLayout(layoutIngresar);

        connect(btnIngresar, &QPushButton::clicked, this, &MainWindow::ingresarDatos);
        connect(btnBuscar, &QPushButton::clicked, this, &MainWindow::buscarDatos);

        // Crear base de datos
        crearTabla();
    }

private:
    QLineEdit *entryBuscar;
    QLineEdit *entryNombre;
    QLineEdit *entryEdad;

    void crearTabla() {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("basededatos.db");

        if (!db.open()) {
            qDebug() << "Error al abrir la base de datos.";
            return;
        }

        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS personas ("
                   "id INTEGER PRIMARY KEY,"
                   "nombre TEXT,"
                   "edad INTEGER)");
    }

    void ingresarDatos() {
        QString nombre = entryNombre->text();
        QString edad = entryEdad->text();

        if (!nombre.isEmpty() && !edad.isEmpty()) {
            agregarPersona(nombre, edad);
            QMessageBox::information(this, "Éxito", "Datos guardados exitosamente.");
            entryNombre->clear();
            entryEdad->clear();
        } else {
            QMessageBox::critical(this, "Error", "Por favor ingrese nombre y edad.");
        }
    }

    void agregarPersona(const QString &nombre, const QString &edad) {
        QSqlQuery query;
        query.prepare("INSERT INTO personas (nombre, edad) VALUES (?, ?)");
        query.addBindValue(nombre);
        query.addBindValue(edad);
        query.exec();
    }

    void buscarDatos() {
        QString nombre = entryBuscar->text();
        if (!nombre.isEmpty()) {
            QSqlQuery query;
            query.prepare("SELECT * FROM personas WHERE nombre = ?");
            query.addBindValue(nombre);
            query.exec();

            if (query.next()) {
                QString resultado = "Nombre: " + query.value(1).toString() + "\nEdad: " + query.value(2).toString();
                QMessageBox::information(this, "Resultado", resultado);
            } else {
                QMessageBox::information(this, "Resultado", "No se encontraron datos.");
            }
        } else {
            QMessageBox::critical(this, "Error", "Por favor ingrese un nombre.");
        }
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow ventana;
    ventana.show();

    return app.exec();
