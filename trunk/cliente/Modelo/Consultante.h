#ifndef CONSULTANTE_H
#define CONSULTANTE_H

#include "Consulta.h"
class Respuesta;

class Consultante {
    public:
        Consultante();
        ~Consultante();

        virtual void hacerConsulta();
        virtual void recibirRespuesta(const Respuesta& rta);

        virtual unsigned getID() const;
    protected:
        Consulta consulta;
        virtual void procesarRespuesta(const Respuesta& rta) = 0;
    private:
        static unsigned generadorID;
        unsigned ID;
        bool esperandoRespuesta;
};

#endif  // CONSULTANTE_H
