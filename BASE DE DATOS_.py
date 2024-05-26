import sqlite3
import tkinter as tk
from tkinter import messagebox

def crear_tabla():
    conexion = sqlite3.connect('basededatos.db')
    cursor = conexion.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS personas (
                        id INTEGER PRIMARY KEY,
                        nombre TEXT,
                        edad INTEGER
                    )''')
    conexion.commit()
    conexion.close()

def agregar_persona(nombre, edad):
    conexion = sqlite3.connect('basededatos.db')
    cursor = conexion.cursor()
    cursor.execute("INSERT INTO personas (nombre, edad) VALUES (?, ?)", (nombre, edad))
    conexion.commit()
    conexion.close()

def buscar_persona(nombre):
    conexion = sqlite3.connect('basededatos.db')
    cursor = conexion.cursor()
    cursor.execute("SELECT * FROM personas WHERE nombre=?", (nombre,))
    persona = cursor.fetchone()
    conexion.close()
    return persona

def ingresar_datos():
    ventana_1 = tk.Toplevel(root)
    ventana_1.title("Ingresar Datos")

    label_nombre = tk.Label(ventana_1, text="Nombre:")
    label_nombre.grid(row=0, column=0)
    entry_nombre = tk.Entry(ventana_1)
    entry_nombre.grid(row=0, column=1)

    label_edad = tk.Label(ventana_1, text="Edad:")
    label_edad.grid(row=1, column=0)
    entry_edad = tk.Entry(ventana_1)
    entry_edad.grid(row=1, column=1)

    def guardar_datos():
        nombre = entry_nombre.get()
        edad = entry_edad.get()
        if nombre and edad:
            agregar_persona(nombre, edad)
            messagebox.showinfo("Éxito", "Datos guardados exitosamente.")
            ventana_1.destroy()
        else:
            messagebox.showerror("Error", "Por favor ingrese nombre y edad.")

    btn_guardar = tk.Button(ventana_1, text="Guardar", command=guardar_datos)
    btn_guardar.grid(row=2, columnspan=2)

def buscar_datos():
    nombre = entry_buscar.get()
    if nombre:
        persona = buscar_persona(nombre)
        if persona:
            messagebox.showinfo("Resultado", f"Nombre: {persona[1]}\nEdad: {persona[2]}")
        else:
            messagebox.showinfo("Resultado", "No se encontraron datos.")
    else:
        messagebox.showerror("Error", "Por favor ingrese un nombre.")

crear_tabla()

root = tk.Tk()
root.title("Base de Datos")

label_buscar = tk.Label(root, text="Buscar Nombre:")
label_buscar.grid(row=0, column=0)
entry_buscar = tk.Entry(root)
entry_buscar.grid(row=0, column=1)

btn_buscar = tk.Button(root, text="Buscar", command=buscar_datos)
btn_buscar.grid(row=0, column=2)

btn_ingresar = tk.Button(root, text="Ingresar Datos", command=ingresar_datos)
btn_ingresar.grid(row=1, columnspan=3)

root.mainloop()
