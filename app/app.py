from flask import Flask, render_template, send_from_directory, request, abort, redirect, url_for
import mysql.connector

app = Flask(__name__)

# Configuración de la base de datos MySQL
db_config = {
    'host': 'localhost',
    'user': 'root',
    'password': '',
    'database': 'basedatoshotel'
}

# Datos de los hoteles
hoteles = {
    1: {
        "nombre": "VVC Hotel's",
        "descripcion": "Ubicado en el corazón de Villavicencio, con vista panorámica y desayuno incluido.",
        "css_class": "hotel1",
        "capacidad": 2
    },
    2: {
        "nombre": "Hotel Estelar",
        "descripcion": "Opciones económicas sin sacrificar comodidad. Wi-Fi gratuito y fácil acceso.",
        "css_class": "hotel2",
        "capacidad": 4
    },
    3: {
        "nombre": "GHL Hotel Grand",
        "descripcion": "Experiencia boutique con piscina y atención personalizada.",
        "css_class": "hotel3",
        "capacidad": 6
    }
}

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/hotel1')
def hotel1():
    hotel = hoteles.get(1)
    return render_template('hotel1.html', hotel=hotel, hotel_id=1)

@app.route('/hotel2')
def hotel2():
    hotel = hoteles.get(2)
    return render_template('hotel2.html', hotel=hotel, hotel_id=2)

@app.route('/hotel3')
def hotel3():
    hotel = hoteles.get(3)
    return render_template('hotel3.html', hotel=hotel, hotel_id=3)

@app.route('/nosotros', methods=['GET', 'POST'])
def nosotros():
    mensaje = ""
    error = ""

    if request.method == 'POST':
        nombre = request.form.get('nombre')
        correo = request.form.get('correo')
        telefono = request.form.get('telefono')
        texto = request.form.get('mensaje')

        print("DEBUG - Datos recibidos:", nombre, correo, telefono, texto)

        try:
            conn = mysql.connector.connect(**db_config)
            cursor = conn.cursor()
            insert_query = "INSERT INTO contacto (Nombre, Telefono, Correo, Mensaje) VALUES (%s, %s, %s, %s)"
            cursor.execute(insert_query, (nombre, telefono, correo, texto))
            conn.commit()
            cursor.close()
            conn.close()
            mensaje = "¡Gracias por contactarnos! Te responderemos pronto."
        except Exception as e:
            import traceback
            traceback.print_exc()
            error = f"Ocurrió un error al guardar el mensaje: {e}"

    return render_template('nosotros.html', mensaje=mensaje, error=error)

@app.route('/destino')
def destino():
    return render_template('destino.html')

@app.route('/reservar/<int:hotel_id>', methods=['GET', 'POST'])
def reservar(hotel_id):
    hotel = hoteles.get(hotel_id)
    if not hotel:
        abort(404)

    if request.method == 'POST':
        nombre = request.form.get('nombre')
        correo = request.form.get('correo')
        telefono = request.form.get('telefono')
        fecha_entrada = request.form.get('fecha_entrada')
        fecha_salida = request.form.get('fecha_salida')
        huespedes = request.form.get('huespedes')
        comentarios = request.form.get('comentarios')

        print("Datos recibidos (reserva):")
        print(nombre, correo, telefono, fecha_entrada, fecha_salida, huespedes, comentarios)

        try:
            conn = mysql.connector.connect(**db_config)
            cursor = conn.cursor()
            insert_query = """
                INSERT INTO reservar 
                (Nombre, Correo, Teléfono, `Fecha de entrada`, `Fecha de salida`, Huéspedes, Comentarios)
                VALUES (%s, %s, %s, %s, %s, %s, %s)
            """
            data = (
                nombre,
                correo,
                telefono,
                fecha_entrada,
                fecha_salida,
                int(huespedes) if huespedes else 0,
                comentarios
            )
            cursor.execute(insert_query, data)
            conn.commit()
            cursor.close()
            conn.close()
            mensaje = "¡Reserva confirmada y almacenada exitosamente!"
        except mysql.connector.Error as err:
            mensaje = f"Ocurrió un error al guardar la reserva: {err}"

        reserva = {
            "hotel": hotel["nombre"],
            "nombre": nombre,
            "correo": correo,
            "telefono": telefono,
            "fecha_entrada": fecha_entrada,
            "fecha_salida": fecha_salida,
            "huespedes": huespedes,
            "comentarios": comentarios
        }

        return render_template('reserva_confirmacion.html', reserva=reserva, mensaje=mensaje)

    return render_template('reservar.html', hotel=hotel, hotel_id=hotel_id)

@app.route('/buscar', methods=['GET', 'POST'])
def buscar():
    hotel_recomendado = None
    mensaje = None

    if request.method == 'POST':
        try:
            personas = int(request.form.get('personas', 0))
        except ValueError:
            personas = 0

        for hid, h in hoteles.items():
            if h["capacidad"] == personas:
                hotel_recomendado = {"id": hid, **h}
                break

        if not hotel_recomendado:
            mayores = [(hid, h) for hid, h in hoteles.items() if h["capacidad"] >= personas]
            if mayores:
                hid, h = sorted(mayores, key=lambda x: x[1]["capacidad"])[0]
                hotel_recomendado = {"id": hid, **h}
            else:
                mensaje = "No tenemos un hotel disponible para esa cantidad de personas."

    return render_template('buscar.html', hotel=hotel_recomendado, mensaje=mensaje)

@app.route('/static/css/<path:filename>')
def custom_static_css(filename):
    return send_from_directory('static/css', filename, mimetype='text/css')

if __name__ == "__main__":
    app.run(debug=True)
