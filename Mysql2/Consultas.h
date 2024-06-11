#pragma once
#include <mysql.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include "DB.h"

using namespace std;
class Consultas
{
public:
    string id_vuelo;
    string id_ruta;
    string id_horario;
    string id_asiento;
    string nombre_usuario;
    string asiento;
    string dia, mes, año, fecha;


    int q_estado;
    MYSQL_ROW fila;
    MYSQL_RES* resultado;
    DB db = DB();

    void Ingresar_Fecha() {
        system("cls");
        cout << "Ingrese el dia que quiere viajar: ";
        getline(cin, dia);
        cout << "Ingrese el mes que quiere viajar (en numeros): ";
        getline(cin, mes);
        cout << "Ingrese el año del viaje: ";
        getline(cin, año);
        fecha = año + "-" + mes + "-" + dia;
        system("cls");
    }

    // metodos de lectura para traer datos de la DB

    
    void setConsoleColor(int textColor, int backgroundColor) {
        int colorAttribute = (backgroundColor << 4) | textColor;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, colorAttribute);
    }
    void Consultar_Vuelos()
    {   
        db.Iniciar_Conexion();
        system("cls");
        cout << "Seleccione una ruta para viajar" << endl;
        string consulta = "SELECT * FROM rutas";
        const char* c = consulta.c_str();
        q_estado = mysql_query(db.GET_conexion(), c);
        if (!q_estado)
        {
            resultado = mysql_store_result(db.GET_conexion());
            while (fila = mysql_fetch_row(resultado))
            {
                cout << fila[0] << "\t" << fila[1] << endl;
            }
            cout << endl;
        }
        getline(cin, id_ruta);
        db.Cerrar_Conexion();
    }

    void Consultar_Horarios()
    {
        db.Iniciar_Conexion();
        system("cls");
        cout << "Seleccione el horario en el que desea viajar" << endl;
        string consulta = "SELECT horarios.id, horarios.horario FROM rutas JOIN vuelos ON rutas.id = vuelos.id_ruta JOIN horarios ON vuelos.id_horario = horarios.id WHERE rutas.id = " + id_ruta;
        const char* c = consulta.c_str();
        q_estado = mysql_query(db.GET_conexion(), c);
        if (!q_estado)
        {
            resultado = mysql_store_result(db.GET_conexion());
            while (fila = mysql_fetch_row(resultado))
            {
                cout << fila[0] << "\t" << fila[1] << endl;
            }
            cout << endl;
        }
        getline(cin, id_horario);
        Obtener_Vuelo();
        db.Cerrar_Conexion();
    }

    void Ingresar_Nombre() {
        db.Iniciar_Conexion();
        system("cls");
        cout << "Ingrese su nombre y apellido" << endl;
        getline(cin, nombre_usuario);
        db.Cerrar_Conexion();
    }

    void Ingresar_Asiento() {
        db.Iniciar_Conexion();
        while (true){
            cout << "Seleccione su asiento (A-D, 1-10)" << endl;
            getline(cin, asiento);
            system("cls");

            string consulta = "SELECT asientos.asiento FROM reserva JOIN asientos ON asientos.id = reserva.id_asiento JOIN vuelos ON vuelos.id = reserva.id_vuelo WHERE asientos.asiento = '" + asiento + "'  AND vuelos.id = " + id_vuelo;
            const char* c = consulta.c_str();
            q_estado = mysql_query(db.GET_conexion(), c);
            if (!q_estado)
            {
                resultado = mysql_store_result(db.GET_conexion());
                if (!(fila = mysql_fetch_row(resultado)))
                {
                    string pedir_asiento = "SELECT asientos.id FROM asientos WHERE asientos.asiento = '"+ asiento +"'";
                    const char* p_a = pedir_asiento.c_str();
                    q_estado = mysql_query(db.GET_conexion(), p_a);
                    if (!q_estado) {
                        resultado = mysql_store_result(db.GET_conexion());
                        if ((fila = mysql_fetch_row(resultado))) {
                            id_asiento = fila[0];
                        }
                    }
                    break;
                }
                else{
                    setConsoleColor(4, 0);
                    cout << "No se puede, asiento ocupado" << endl << endl;
                    setConsoleColor(9, 0);
                };
            }
        }
        db.Cerrar_Conexion();
    }

    void Registrar_Reserva() {
        db.Iniciar_Conexion();
        string insertar = "INSERT INTO reserva(id_vuelo, id_asiento, pasajero, fecha) values("+ id_vuelo + ", "+ id_asiento + ", '"+ nombre_usuario +"', '"+ fecha +"')";
        const char* i = insertar.c_str();
        q_estado = mysql_query(db.GET_conexion(), i);

        if (!q_estado) {
            string consulta = "SELECT id FROM reserva WHERE reserva.id_vuelo = " + id_vuelo + " AND reserva.id_asiento = " + id_asiento + " AND pasajero = '" + nombre_usuario+"'";
            const char* c = consulta.c_str();
            q_estado = mysql_query(db.GET_conexion(), c);

            if (!q_estado) {
                resultado = mysql_store_result(db.GET_conexion());
                if (fila = mysql_fetch_row(resultado)) {
                    cout << "Tu numero de reserva es el " << fila[0]<< endl << endl;
                    system("pause");
                }
            }
        }

        db.Cerrar_Conexion();
    }

    void Obtener_Vuelo() {
        string consulta_vuelo = "SELECT vuelos.id FROM vuelos JOIN horarios ON horarios.id = vuelos.id_horario JOIN rutas ON rutas.id = vuelos.id_ruta WHERE rutas.id = " + id_ruta + " AND horarios.id = " + id_horario;
        const char* cv = consulta_vuelo.c_str();
        q_estado = mysql_query(db.GET_conexion(), cv);
        if (!q_estado) {
            resultado = mysql_store_result(db.GET_conexion());
            if ((fila = mysql_fetch_row(resultado))) {
                id_vuelo = fila[0];
            }
        }
    }
};
