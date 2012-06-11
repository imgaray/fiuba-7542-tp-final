#ifndef CONSULTANTE_H
#define CONSULTANTE_H

#include "PadreDeConsultantes.h"
#include "Consulta.h"
class Respuesta;
class ServidorRemoto;

class Consultante : public PadreDeConsultantes {
    public:
        Consultante();
        ~Consultante();

        virtual void hacerConsulta(ServidorRemoto& server);
        virtual void cancelarConsulta(ServidorRemoto& server);
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
