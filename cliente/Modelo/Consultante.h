#ifndef CONSULTANTE_H
#define CONSULTANTE_H

class Respuesta;

class Consultante {
    public:
        Consultante();
        ~Consultante();
        void hacerConsulta() const;
        void recibirRespuesta(const Respuesta& rta);
        unsigned getID() const;
    protected:
        Consulta consulta;
    private:
        static unsigned generadorID;
        unsigned ID;
        bool esperandoRespuesta;
};

#endif  // CONSULTANTE_H
