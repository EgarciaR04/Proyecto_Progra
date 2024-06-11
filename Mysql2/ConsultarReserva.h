#pragma once
#include <mysql.h>
#include <iostream>
#include <string>
#include "DB.h"

using namespace std;

class ConsultarReserva
{
public:
	string id_reserva;

	int q_estado;
	MYSQL_ROW fila;
	MYSQL_RES* resultado;
	DB db = DB();

	void Consultar_Reserva() {
		db.Iniciar_Conexion();
		

		cout << "Ingrese su numero de reserva: " << endl;
		getline(cin, id_reserva);
		

		string consulta_reserva = "SELECT reserva.id, reserva.pasajero, asientos.asiento, rutas.direccion, horarios.horario, reserva.fecha, reserva.volado FROM reserva JOIN asientos ON reserva.id_asiento = asientos.id JOIN vuelos ON reserva.id_vuelo = vuelos.id JOIN rutas ON vuelos.id_ruta = rutas.id JOIN horarios ON horarios.id = vuelos.id_horario WHERE reserva.id = " + id_reserva;
		const char* c_r = consulta_reserva.c_str();
		q_estado = mysql_query(db.GET_conexion(), c_r);

		if (!q_estado) {

			cout << "id\tReserva a nombre de:\tAsiento:\tRuta:\t\tHorario:\tFecha:\tVolado:" << endl;

			resultado = mysql_store_result(db.GET_conexion());
			while (fila = mysql_fetch_row(resultado)) {
				cout << fila[0] << "\t" << fila[1] << "\t\t" << fila[2] << "\t\t" << fila[3] << "\t\t" << fila[4] << "\t" << fila[5] << "\t" << fila[6] << endl<< endl;
			}
		}

		db.Cerrar_Conexion();
	}
};

