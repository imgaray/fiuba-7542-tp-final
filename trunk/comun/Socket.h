/* 
 * File:   Socket.h
 * Author: migue
 *
 * Created on 26 de abril de 2012, 13:15
 */

#ifndef SOCKET_H
#define	SOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string>

#define TAM_BUFFER 128
#include "Definiciones.h"

class Mensaje;
class Consulta;
class Respuesta;

class Socket {
public:
    /*
     * Constructor para el Socket que recibe el puerto en donde
     * se va a conectar
     */
    explicit Socket(Puerto puerto);
        
    /*
     * Destructor virtual de Socket
     */
    virtual ~Socket();
    
    /*
     * Establece la conexion con
     */
    void conectar(const std::string& huesped);
    
    /*
     * Enlaza el Socket para poder escuchar conexiones entrantes
     */
    void enlazar();
    
    /*
     * Escucha una conexion entrante y retorna un Socket para
     * realizar la comunicion con esta.
     */
    Socket* escucharConexion();
    
    /*
     * Envia el mensaje atravez
     */
    bool enviar(const Mensaje& mensaje);

    // bool recibir(Consulta& consulta);
    
    // bool recibir(Respuesta& respuesta);

    /*
	 * Se pone en espera a recibir una respuesta.
	 */
    bool recibir(Mensaje& mesaje);
    /*
     * Cierra la conexion.
     */
    void desconectar();
    
    /*
     * Retorna un bool indicando si el socket se encuentra
     * en estado de conectado.
     */
    bool conectado();
private:
    /*
     * Constructor que recibe un "file descriptor" ya inicializado
     */
    explicit Socket(int fd);
    
    /*
     * Metodo que guarda lo recibido del socket en el string datos.
     * hasta tener un mensaje completo.
     */
    bool recibirDatos(std::string& datos);

    /*
     * Constructor copia privado.
     */
    Socket(const Socket& orig) {}
    void operator=(const Socket& orig) {}
    
    /*
     * Metodo privado que inicializa los atributos basicos
     */
    void inicializar();
    
    struct timeval _timeout;
    int _fd;
    struct sockaddr_in _direccion;
    Puerto _puerto;
    bool _conectado;
    bool _enlazado;
    char _buffer[TAM_BUFFER];
};

#endif	/* SOCKET_H */

