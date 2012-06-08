#ifndef CONSULTANTE_H
#define CONSULTANTE_H

class Respuesta;

class Consultante {
    public:
        Consultante();
        ~Consultante();

        void hacerConsulta() const;
        virtual void recibirRespuesta(const Respuesta& rta);

        virtual unsigned getID() const;
    protected:
        Consulta consulta;
        virtual void procesarRespuesta(const Respuesat& rta) = 0;
    private:
        static unsigned generadorID;
        unsigned ID;
        bool esperandoRespuesta;
};

#endif  // CONSULTANTE_H
