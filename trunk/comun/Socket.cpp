/* 
 * File:   Socket.cpp
 * Author: migue
 * 
 * Created on 26 de abril de 2012, 13:15
 */

#include "Socket.h"
#include "Consulta.h"
#include "Respuesta.h"
#include "Definiciones.h"
#include <iostream>
// #include "common-Mensaje.h"
#include <cstring>
#include <cerrno>
#include <csignal>
#define MYPRINT(c) std::cout << "SOCKET DEBUG " <<(c) << std::endl


// extern int errno;

#define CONEX_EN_ESPERA 10

Socket::Socket(Puerto puerto) {
    this->inicializar();
    
    this->_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (this->_fd == -1) {
        perror("Error al crear el fd de Socket.");
        printf(" Error: %s\n", strerror(errno));
    }
    
    this->_puerto = puerto;
}

Socket::Socket(int fd) {
    this->inicializar();
    this->_conectado = true;
    this->_fd = fd;
}

Socket::~Socket() {    
    close(this->_fd);
}

void Socket::inicializar() {
    this->_fd = 0;
    this->_enlazado = false;
    this->_conectado = false;
    this->_puerto = 0;
}

void Socket::enlazar() {
    memset((char *)&_direccion, 0, sizeof(_direccion));
    _direccion.sin_family = AF_INET;
    _direccion.sin_port = htons(_puerto);
    _direccion.sin_addr.s_addr = INADDR_ANY;
    
    if (bind( _fd,
        (struct sockaddr *)&_direccion,
        (socklen_t)sizeof(struct sockaddr)) >= 0 ) {
        _enlazado = true;
        listen(_fd, CONEX_EN_ESPERA);
    }
    else {
        perror("Enlace de Socket fallido. ");
         printf("Error: %s\n", strerror(errno));
    }
}

Socket* Socket::escucharConexion() {
    if (_enlazado == false)
        return NULL;  
    
    Socket *nsocket = NULL;
    int fd = 0; 
    struct sockaddr_in nuevaDir;
    unsigned int cli_tam = (socklen_t) sizeof(nuevaDir);

    // Acepto la conexion entrante
    fd = accept(_fd, (struct sockaddr *)&nuevaDir, &cli_tam);
    
    if (_enlazado) {
        nsocket = new Socket(fd);
        memcpy(&nsocket->_direccion, &nuevaDir, sizeof(nuevaDir));
    }
    
    return nsocket;
}

void Socket::conectar(const std::string& huesped) {
    if (_enlazado == true || _conectado == true)
        return;
    
    struct hostent *he;
    
    he = gethostbyname(huesped.c_str());
    if (he == NULL) {
        perror("Error al obtener le Host. ");
        printf("Error: %s \n", strerror(errno));
        _conectado = true;
        return;
    }
//    else {
//    	this->_timeout.tv_sec = 100;
//    	this->_timeout.tv_usec = 0;
//
//    	if (setsockopt(_fd, SOL_SOCKET, SO_SNDTIMEO, (void*) &_timeout, sizeof(_timeout)) == -1) {
//    		desconectar();
//    		return;
//    	}
//   }
        
    _direccion.sin_family = AF_INET; 
    _direccion.sin_port = htons(_puerto); 
    _direccion.sin_addr = *((struct in_addr *)he->h_addr);
    memset(&(_direccion.sin_zero), 8, sizeof(int)); 
    
    
    int resConexion = connect(_fd, 
            (struct sockaddr *)&_direccion,
            sizeof(struct sockaddr));
    
    if (resConexion == -1) {
        perror("Error al conectar. ");
         printf(" Error: %s\n", strerror(errno));
        _conectado = false;
        return;
    }
    
    this->_conectado = true;
}

void Socket::desconectar() {
    this->_conectado = false;
    this->_enlazado = false;
    
    if (shutdown(_fd, SHUT_RDWR) == -1) {
		if (errno != ENOTCONN)	
			perror("Error al cerrar conexion de Socket. ");
    }
}

bool Socket::enviar(const Mensaje& mensaje) {
	std::string s_datos = mensaje.serializar();
	std::cout << "Socket--Datos a enviar: \"" << s_datos <<"\"" <<std::endl;

    const char* datos = s_datos.c_str(); // consulta.datos();
    size_t tam_datos = s_datos.size(); // consulta.tamanio();
    size_t cant_enviada = 0;
    int envActual = 0;
    
    while (cant_enviada < tam_datos && _conectado) {
        envActual = send(_fd, 
                datos + cant_enviada, 
                (tam_datos - cant_enviada), 
                0);
        if (envActual < 0) {
			 _conectado = false;
		} else {
			cant_enviada += envActual;
		}
      //  std::cout << "cantidad enviada = " << cant_enviada << std::endl;
    }

    std::cout << "Socket--TODOS LOS DATOS ENVIADOS******" << std::endl;

    return _conectado;
}


bool Socket::recibir(Mensaje& mensaje) {
	std::string datos;
	datos.clear();
	bool ok = recibirDatos(datos);

	std::cout << "Socket---Datos que llegaron: \"" << datos << "\"" << std::endl;

	if (ok) {
		mensaje.deserializar(datos);
	}


	return ok;
}

bool Socket::recibirDatos(std::string& datos){
//	std::string aux;

	int recibidos = 0;
	bool finDeMensaje = false;
	char buff;
	datos.clear();

	while (finDeMensaje == false && _conectado) {
		//recibidos = recv(_fd, _buffer,sizeof(char)*TAM_BUFFER, 0);
		recibidos = recv(_fd, &buff,sizeof(char), 0);
		if (recibidos < 0) {
			perror("Error al recibir. ");
			printf("Error: %s\n", strerror(errno));
			_conectado = false;
		} else if (recibidos > 0) {
			//aux.clear();
			//aux.append(_buffer, recibidos);

		//	MYPRINT(recibidos);
			datos += buff;

			finDeMensaje = (buff == sep_fin);

		} //else if (recibidos == 0) {
		//	_conectado = false;
	//	}
	//	std::cout << "Socket-Tanda de datos recibidas..." << std::endl;
	}
	std::cout << "Socket- Recibido "<< datos << std::endl;
	return _conectado;
}



bool Socket::conectado() {
    return this->_conectado;
}
