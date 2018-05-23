/// Autor: Víctor Uc Cetina (uccetina@uady.mx)
#ifndef ADABOOST_H_
#define ADABOOST_H_

#include <string>
#include <vector>
using namespace std;

class Datos;
class ClasificadorFuerte;
class ClasificadorDebil;

struct Particiones{
		vector< vector<float> > xTrain;
		vector<short> yTrain;
		vector< vector<float> > xTest;
		vector<short> yTest;
};

struct PlantillaHaar1D{
		unsigned short tipo;
		unsigned short tamano;
		unsigned short inicio;
};

struct ParamClasificador{
		double umbral;
		short polaridad;
};

class Datos{
	private:
		vector< vector<float> > x;
		vector<short> y;
		
	public:
		void leeArchivoDatos(string directorioDatos, string archDatosX, string archDatosY);
		vector< vector<float> > X() const;
		vector<short> Y() const;
		void printX();
		void printY();	
};

class ClasificadorFuerte{
	private:
		vector< vector<float> > x;
		vector<short> y;
		vector< vector<float> > xIntegral;
		unsigned short longitudEjemplo;
		unsigned int numEjemplos;
		unsigned short numClasiDebiles;
		vector< ClasificadorDebil > debil;
		unsigned short MIN_TAMANO_PLANTILLA;
		unsigned short MAX_TAMANO_PLANTILLA;
		vector<struct PlantillaHaar1D> catalogoPlantillasHaar1D;
	
	public:
		ClasificadorFuerte(vector< vector<float> > _x, vector<short> _y, unsigned short _numClasiDebiles, unsigned short _MIN_TAM_PLAN, unsigned short _MAX_TAM_PLAN);
		/// Returners
		vector< vector<float> > X() const;
		vector<short> Y() const;
		unsigned short NumClasiDebiles() const;
		/// Printers
		void printX();
		void printY();
		void printDebiles();
		/// Algorithms
		void creaCatalogoPlantillas();
		void generaDebiles();
		void pruebaDebiles(vector< vector<float> > datosX, vector<short> datosY);
};

class ClasificadorDebil{
	private:
		double alfa;
		double error;
		vector<double> distribucion;
		struct PlantillaHaar1D plantilla;
		struct ParamClasificador parametros;
		
	public:
		/// Setters
		void setAlfa(double _alfa);
		void setDistribucion(vector<double> _tmpDistribucion);
		void setPlantilla(const struct PlantillaHaar1D & tmpPlantilla);
		void setParametros(struct ParamClasificador tmpParametros);
		/// Returners
		double Alfa() const;
		double Error() const;
		double Umbral() const;
		short Polaridad() const;
		unsigned short Tipo() const;
		unsigned short Tamano() const;
		unsigned short Inicio() const;
		double Distribucion(unsigned int _idx) const;
		/// Printers
		void printDebil();
		void printDistribucion();
		/// Algorithms
		void encuentraMejorClasificador(const vector< vector<float> > & xIntegral,
											const vector< vector<float> > & x, 
											const vector<short> & y, 
											unsigned int numEjemplos,
											const vector<struct PlantillaHaar1D> & catalogoPlantillasHaar1D);
		short evaluaEjemplo(const vector<float> & xIntegralRenglon) const;
		short evaluaEjemplo(const vector<float> & xIntegralRenglon, const struct PlantillaHaar1D & tmpPlantilla, 
									struct ParamClasificador tmpParametros) const;
		double calculaError(const vector< vector<float> > & xIntegral, const vector<short> & y, unsigned int numEjemplos,
									const struct PlantillaHaar1D & tmpPlantilla, struct ParamClasificador tmpParametros);
		struct ParamClasificador seleccionaMejorCaracteristica(const vector< vector<float> > & xIntegral, const vector<short> & y, 
									const struct PlantillaHaar1D & tmpPlantilla);
};

#endif
