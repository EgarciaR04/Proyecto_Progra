#include <iostream>
#include <string>
#include <Windows.h>
#include <sstream>
#include "Consultas.h"
#include "ConsultarReserva.h"

using namespace std;

void setConsoleColor(int textColor, int backgroundColor) {
    int colorAttribute = (backgroundColor << 4) | textColor;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorAttribute);
}

int main(){
    Consultas consulta_reservar;
    ConsultarReserva consultar_reserva;
    setConsoleColor(9, 0);
    while (true)
    {
        system("cls");
        string seleccion;
        cout << "-----------------------------------------" << endl;
        cout << "Seleccione lo que desea realizar" << endl;
        cout << "1) Ver mi reserva" << endl;
        cout << "2) Realizar nueva reserva" << endl;
        cout << "3) Salir" << endl;
        cout << "-----------------------------------------" << endl;
        getline(cin, seleccion);

        system("cls");

        if (seleccion == "1")
        {
            consultar_reserva.Consultar_Reserva();
            system("pause");
        }
        else if (seleccion == "2") {
            consulta_reservar.Ingresar_Fecha();
            consulta_reservar.Consultar_Vuelos();
            consulta_reservar.Consultar_Horarios();
            consulta_reservar.Ingresar_Nombre();
            consulta_reservar.Ingresar_Asiento();
            consulta_reservar.Registrar_Reserva();
        }
        else if (seleccion == "3")
        {
            break;
        }
        else {
            cout << "Ingrese un dato valido"<< endl << endl;
        }
    }
}

/*
        Forma correcta de hacer cosas en la base de datos, usando lenguaje sql

        string update = "UPDATE vuelo SET id_asiento = 1 WHERE id = 2";
        const char* i = update.c_str();
        q_estado = mysql_query(conexion, i);


        ------------------------------------------------------------------------

        Forma correcta de hacer consultas en la base de datos

        string consulta = "SELECT * FROM asientos";
        const char* c = consulta.c_str();
        q_estado = mysql_query(conexion, c);

        resultado = mysql_store_result(conexion);
            while (fila = mysql_fetch_row(resultado))
            {
                cout << fila[0] << "\t" << fila[1] << endl;
            }

        */