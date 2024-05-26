import sqlite3

# Conectar a la base de datos (se creará si no existe)
conexion = sqlite3.connect('basededatos.db')

# Crear un cursor
cursor = conexion.cursor()

# Crear una tabla (si no existe)
cursor.execute('''CREATE TABLE IF NOT EXISTS usuarios (
                    id INTEGER PRIMARY KEY,
                    nombre TEXT NOT NULL,
                    edad INTEGER
                )''')

# Insertar datos
cursor.execute("INSERT INTO usuarios (nombre, edad) VALUES (?, ?)", ('Juan', 30))
cursor.execute("INSERT INTO usuarios (nombre, edad) VALUES (?, ?)", ('María', 25))

# Guardar los cambios
conexion.commit()

# Consultar datos
cursor.execute("SELECT * FROM usuarios")
usuarios = cursor.fetchall()

# Mostrar los datos
print("Usuarios:")
for usuario in usuarios:
    print(usuario)

# Cerrar la conexión
conexion.close()
