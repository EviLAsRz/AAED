#include <iostream>
#include "../clasicos/PilaEnla.h"
#include "../clasicos/ListaEnla.h"
#include <string>
/*
 * IMPORTANTE: FUNCIÓN BUSCAR DE LA LISTA DESAPARECE, HAY QUE CAMBIAR LOS MÉTODOS IMPLEMENTADOS CON ESTA FUNCIÓN
 */
struct Medico
{
	string nombre;
	ColaDin<string>C_pacientes;
	Medico(const string& n): nombre(n){}
	bool operator = (const Medico& m) { return nombre == m.nombre; }
};

class Consultorio
{
	public:
		Consultorio() = default;
		~Consultorio() = default;
		void darAltaMedico(const Medico& m);
		void eliminaMedico(const Medico& m);
		void agregarPaciente(const Medico& m, const string& p);
		void atenderPaciente(const Medico& m);
		const string& siguiente(const Medico& m);
		bool colaVacia(const Medico& m);

	private:
		ListaEnla<Medico>lsMedicos;
};

int main() { return 0; }

void Consultorio::darAltaMedico(const Medico& m)
{
	auto p = lsMedicos.buscar(m);
	assert( p == lsMedicos.fin() && "El médico ya está en la lista");
	ListaMedicos.insertar(m,p);
}

void Consultorio::eliminaMedico( const Medico& m)
{
	auto p = lsMedicos.buscar(m);
	assert(p != lsMedicos.fin() && "El médico no está en la lista");
	lsMedicos.eliminar(p);
}

void Consultorio::agregarPaciente(const Medico& m, const string& p)
{
	auto p = lsMedicos.buscar(m);
	assert(p != lsMedicos.fin());
	lsMedicos.elemento(p).C_pacientes.push(p);
}

void Consultorio::atenderPaciente(const Medico& m)
{
	auto p = lsMedicos.buscar(m);
	assert(p != lsMedicos.fin());
	lsMedicos.elemento(p).C_pacientes.pop();
}

const string& Consultorio::siguiente(const Medico& m)
{
	auto p = lsMedicos.buscar(m);
	assert(p != lsMedicos.fin());
	lsMedicos.elemento(p).C_pacientes.frente();
}

bool Consultorio::colaVacia(const Medico& m)
{
	auto p = lsMedicos.buscar(m);
	assert(p != lsMedicos.fin());
	return lsMedicos.elemento(p).C_pacientes.vacia();
}
