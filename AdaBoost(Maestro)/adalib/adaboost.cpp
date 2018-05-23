/// Autor: Víctor Uc Cetina (uccetina@uady.mx)
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include "adaboost.h"
using namespace std;

vector<struct Particiones> generaParticionesCV(Datos misDatos, unsigned short numParticiones)
{
	struct Particiones par;
	vector<struct Particiones> vectorParticiones;

	unsigned int numEjemplos = misDatos.Y().size();
	unsigned int numEjemplosPositivos = numEjemplos/2;
	unsigned short tamParticion = numEjemplosPositivos/numParticiones;

	vector< vector<float> >::iterator iniX, finX;
	vector<short>::iterator iniY, finY;

	for(unsigned short i=0; i<numParticiones; i++)
	{
		par.xTrain = misDatos.X();
		par.yTrain = misDatos.Y();

		for(unsigned short j = (i*tamParticion); j < ( (i*tamParticion)+tamParticion ); j++)
		{
			par.xTest.push_back(par.xTrain[j]);
			par.yTest.push_back(par.yTrain[j]);
		}
		for(unsigned short j = ( (i*tamParticion)+numEjemplosPositivos ); j < ( (i*tamParticion)+numEjemplosPositivos+tamParticion ); j++)
		{
			par.xTest.push_back(par.xTrain[j]);
			par.yTest.push_back(par.yTrain[j]);
		}

		iniX = par.xTrain.begin() + (i*tamParticion) + numEjemplosPositivos;
		finX = iniX + tamParticion;
		par.xTrain.erase(iniX, finX);

		iniX = par.xTrain.begin() + (i*tamParticion);
		finX = iniX + tamParticion;
		par.xTrain.erase(iniX, finX);

		iniY = par.yTrain.begin() + (i*tamParticion) + numEjemplosPositivos;
		finY = iniY + tamParticion;
		par.yTrain.erase(iniY, finY);

		iniY = par.yTrain.begin() + (i*tamParticion);
		finY = iniY + tamParticion;
		par.yTrain.erase(iniY, finY);
		

		vectorParticiones.push_back(par);

		par.xTrain.clear();
		par.yTrain.clear();
		par.xTest.clear();
		par.yTest.clear();
	}
		
	return vectorParticiones;
}

///===
///=== Definición de la clase Datos
///===

void Datos::leeArchivoDatos(string directorioDatos, string archDatosX, string archDatosY)
{
	string strArchivoX, strArchivoY;
	strArchivoX = directorioDatos + archDatosX;
	strArchivoY = directorioDatos + archDatosY;
	unsigned int numRenglones;
	unsigned int numColumnas;
	vector<float> tmpVecX;
	float floatVal;
	short intVal;
	
	ifstream archivoX( strArchivoX.c_str() );
	archivoX >> numRenglones;
	archivoX >> numColumnas;
	
	for(unsigned int i=0; i<numRenglones; i++)
	{
		for(unsigned int j=0; j<numColumnas; j++)
		{
			archivoX >> floatVal;
			tmpVecX.push_back(floatVal);
		}
		x.push_back(tmpVecX);
		tmpVecX.clear();
	}
	
	ifstream archivoY( strArchivoY.c_str() );
	
	for(unsigned int i=0; i<numRenglones; i++)
	{
		archivoY >> intVal;
		y.push_back(intVal);
	}
}

vector< vector<float> > Datos::X() const
{
	return x;
}

vector<short> Datos::Y() const
{
	return y;
}

void Datos::printX()
{
	vector< vector<float> >::iterator renglon;
	vector<float>::iterator columna;
	
	cout << "x = " << endl;
	for(renglon = x.begin(); renglon != x.end(); ++renglon)
	{
		for(columna = renglon->begin(); columna != renglon->end(); ++columna)
			cout << *columna << "  ";
		cout << endl;
	}
}

void Datos::printY()
{
	cout << endl << "y = " << endl;
	for(vector<short>::iterator it = y.begin(); it != y.end(); ++it)
		cout << *it << endl;
}

///===
///=== Definición de la clase ClasificadorFuerte
///===

ClasificadorFuerte::ClasificadorFuerte(vector< vector<float> > _x, vector<short> _y, unsigned short _numClasiDebiles, unsigned short _MIN_TAM_PLAN, unsigned short _MAX_TAM_PLAN)
{
	x = _x;
	y = _y;
	xIntegral = x;
	
	numClasiDebiles = _numClasiDebiles;
	longitudEjemplo = x[0].size();
	numEjemplos = y.size();
	
	MIN_TAMANO_PLANTILLA = _MIN_TAM_PLAN;
	MAX_TAMANO_PLANTILLA = _MAX_TAM_PLAN;
	creaCatalogoPlantillas();
	
	/// Crea la curva integral
	vector< vector<float> >::iterator renglon;
	vector<float>::iterator columna, columnaAnterior;
	for(renglon = xIntegral.begin(); renglon != xIntegral.end(); ++renglon)
		for(columna = renglon->begin()++; columna != renglon->end(); ++columna)
		{
			columnaAnterior = columna-1;
			*columna += *columnaAnterior;
		}		
}

vector< vector<float> > ClasificadorFuerte::X() const
{
	return x;
}

vector<short> ClasificadorFuerte::Y() const
{
	return y;
}

unsigned short ClasificadorFuerte::NumClasiDebiles() const
{
	return numClasiDebiles;
}

void ClasificadorFuerte::printX()
{
	vector< vector<float> >::iterator renglon;
	vector<float>::iterator columna;
	
	cout << "x = " << endl;
	for(renglon = x.begin(); renglon != x.end(); ++renglon)
	{
		for(columna = renglon->begin(); columna != renglon->end(); ++columna)
			cout << *columna << "  ";
		cout << endl;
	}
}

void ClasificadorFuerte::printY()
{
	cout << endl << "y = " << endl;
	for(vector<short>::iterator it = y.begin(); it != y.end(); ++it)
		cout << *it << endl;
}

void ClasificadorFuerte::printDebiles()
{
	cout << endl << "<<<<< Clasificadores débiles >>>>>" << endl;
	for(unsigned short i=0; i<numClasiDebiles; i++)
	{
		cout << endl << "<<< Débil(" << i+1 << ") >>>";
		debil[i].printDebil();
	}
}

void ClasificadorFuerte::creaCatalogoPlantillas()
{
	struct PlantillaHaar1D tmpPlantilla;
	unsigned short tip;
	
	if( MIN_TAMANO_PLANTILLA > ClasificadorFuerte::longitudEjemplo )
	{
		cerr << endl << "ADVERTENCIA : El tamaño MÍNIMO por default de la Plantilla Haar 1D es mayor que la longitud de los ejemplos"
			<< " (" << (MIN_TAMANO_PLANTILLA) << " > " << ClasificadorFuerte::longitudEjemplo << ")... "
			<< "Se cambió automáticamente MIN_TAMANO_PLANTILLA a 1." << endl;
			
		MIN_TAMANO_PLANTILLA = 1;
	}
	else
		cout << endl << "MIN_TAMANO_PLANTILLA = " << MIN_TAMANO_PLANTILLA << endl;
	
	if( (2*MAX_TAMANO_PLANTILLA) > ClasificadorFuerte::longitudEjemplo )
	{
		cerr << endl << "ADVERTENCIA : El tamaño MÁXIMO por default de la Plantilla Haar 1D es mayor que la longitud de los ejemplos"
			<< " (" << (2*MAX_TAMANO_PLANTILLA) << " > " << ClasificadorFuerte::longitudEjemplo << ")... "
			<< "Se cambió automáticamente MAX_TAMANO_PLANTILLA a un tamaño válido." << endl;
			
		MAX_TAMANO_PLANTILLA = ClasificadorFuerte::longitudEjemplo / 2;
	}
	else
		cout << endl << "MAX_TAMANO_PLANTILLA = " << MAX_TAMANO_PLANTILLA << endl;
	
	tip = 0;
	for(unsigned short tam = MIN_TAMANO_PLANTILLA; tam <= MAX_TAMANO_PLANTILLA; tam++)
		for(unsigned ini = 0; ini <= ( ClasificadorFuerte::longitudEjemplo - tam ); ini++)
		{
			tmpPlantilla.tipo = tip;
			tmpPlantilla.tamano = tam;
			tmpPlantilla.inicio = ini;
			catalogoPlantillasHaar1D.push_back(tmpPlantilla);
		}
	
	tip = 1;
	for(unsigned short tam = MIN_TAMANO_PLANTILLA; tam <= MAX_TAMANO_PLANTILLA; tam++)
		for(unsigned ini = 0; ini <= ( ClasificadorFuerte::longitudEjemplo - (2*tam) ); ini++)
		{
			tmpPlantilla.tipo = tip;
			tmpPlantilla.tamano = tam;
			tmpPlantilla.inicio = ini;
			catalogoPlantillasHaar1D.push_back(tmpPlantilla);
		}
}

void ClasificadorFuerte::generaDebiles()
{
	ClasificadorDebil tmpDebil;
	double tmpAlfa;
	
	vector<double> tmpDistribucion;
	double tmpDoubleVal = (double)1 / ClasificadorFuerte::numEjemplos;
	for(unsigned int i=0; i<ClasificadorFuerte::numEjemplos; i++)
		tmpDistribucion.push_back(tmpDoubleVal);
	
	for(unsigned short i=0; i<numClasiDebiles; i++)
	{
		tmpDebil.setDistribucion(tmpDistribucion);
		tmpDebil.encuentraMejorClasificador(xIntegral, x, y, numEjemplos, catalogoPlantillasHaar1D);
		tmpAlfa = 0.5 * log( ( 1 - tmpDebil.Error() ) / (tmpDebil.Error()+0.0001) );
		tmpDebil.setAlfa(tmpAlfa);
		
		debil.push_back(tmpDebil);
				
		/// Actualizamos la distribucion para el siguiente clasificador débil
		float Z = 0.0;
		for(unsigned int j=0; j<numEjemplos; j++)
		{
			tmpDistribucion[j] = debil[i].Distribucion(j) * exp ( (-1) * debil[i].Alfa() * y[j] * debil[i].evaluaEjemplo( xIntegral[j]) );
			Z += tmpDistribucion[j];
		}
		for(unsigned int j=0; j<numEjemplos; j++)
			tmpDistribucion[j] /= Z;
		
	}
}

void ClasificadorFuerte::pruebaDebiles(vector< vector<float> > datosX, vector<short> datosY)
{
	vector< vector<float> > xPrueba, xPruebaIntegral;
	xPrueba = datosX;
	xPruebaIntegral = xPrueba;
	vector<short> yPrueba = datosY;
	unsigned int numEje = yPrueba.size();
	
	/// Crea la curva integral
	vector< vector<float> >::iterator renglon;
	vector<float>::iterator columna, columnaAnterior;
	for(renglon = xPruebaIntegral.begin(); renglon != xPruebaIntegral.end(); ++renglon)
		for(columna = renglon->begin()++; columna != renglon->end(); ++columna)
		{
			columnaAnterior = columna-1;
			*columna += *columnaAnterior;
		}
	
	unsigned short numFallos = 0;
	short eval;
	float suma;
	cout << endl;
	for(unsigned short j=0; j<numEje; j++)
	{
		suma = 0.0;
		for(unsigned short i=0; i<numClasiDebiles; i++)
			suma += ( debil[i].Alfa() * debil[i].evaluaEjemplo(xPruebaIntegral[j]) );
			
		if( suma > 0 )
		{
			eval = 1;
			if(eval != yPrueba[j])
				numFallos++;
			cout << "(" << j+1 << ") " << suma << " : " << eval << " | ";
		}
		else
		{
			eval = -1;
			if(eval != yPrueba[j])
				numFallos++;
			cout << "(" << j+1 << ") " << suma << " : " << eval << " | ";
		}
	}
	
	float porcentajeFallos = (float)numFallos/numEje*100;
	cout << endl << endl << "Número de fallos = " << numFallos << " de " << numEje << " ("<< porcentajeFallos << "%)" << endl << endl;
	
}

///===
///=== Definición de la clase ClasificadorDebil
///===

void ClasificadorDebil::setAlfa(double _alfa)
{
	alfa = _alfa;
}

void ClasificadorDebil::setDistribucion(vector<double> _tmpDistribucion)
{
	distribucion = _tmpDistribucion;
}

void ClasificadorDebil::setPlantilla(const struct PlantillaHaar1D & tmpPlantilla)
{
	plantilla = tmpPlantilla;
}

void ClasificadorDebil::setParametros(struct ParamClasificador tmpParametros)
{
	parametros = tmpParametros;
}

double ClasificadorDebil::Alfa() const
{
	return alfa;
}

double ClasificadorDebil::Error() const
{
	return error;
}

double ClasificadorDebil::Umbral() const
{
	return parametros.umbral;
}

short ClasificadorDebil::Polaridad() const
{
	return parametros.polaridad;
}

unsigned short ClasificadorDebil::Tipo() const
{
	return plantilla.tipo;
}

unsigned short ClasificadorDebil::Tamano() const
{
	return plantilla.tamano;
}

unsigned short ClasificadorDebil::Inicio() const
{
	return plantilla.inicio;
}

double ClasificadorDebil::Distribucion(unsigned int _idx) const
{
	return distribucion[_idx];
}

void ClasificadorDebil::printDebil()
{
	cout << endl << "alfa = "  << Alfa();
	cout << endl << "error = "  << Error();
	cout << endl << "tipo = "  << Tipo();
	cout << endl << "tamano = "  << Tamano();
	cout << endl << "inicio = "  << Inicio();
	cout << endl << "umbral = "  << Umbral();
	cout << endl << "polaridad = "  << Polaridad();
	cout << endl;
	//printDistribucion();
}

void ClasificadorDebil::printDistribucion()
{
	vector<double>::iterator it;
	cout << endl << "distribucion = " << endl;
	for(it = distribucion.begin(); it != distribucion.end(); ++it)
		cout << *it << endl;
}

void ClasificadorDebil::encuentraMejorClasificador(const vector< vector<float> > & xIntegral,
													const vector< vector<float> > & x, 
													const vector<short> & y, 
													unsigned int numEjemplos,
													const vector<struct PlantillaHaar1D> & catalogoPlantillasHaar1D)
{
	struct ParamClasificador tmpParametros;
	double tmpError;
	ClasificadorDebil::error = 1.0;
	
	for(unsigned short idx = 0; idx < catalogoPlantillasHaar1D.size(); idx++)
	{
		tmpParametros = seleccionaMejorCaracteristica(xIntegral, y, catalogoPlantillasHaar1D[idx]);
		tmpError = calculaError(xIntegral, y, numEjemplos, catalogoPlantillasHaar1D[idx], tmpParametros);
	
		if(tmpError < ClasificadorDebil::error)
		{
			ClasificadorDebil::error = tmpError;
			setPlantilla(catalogoPlantillasHaar1D[idx]);
			setParametros(tmpParametros);
		}
	}
}

short ClasificadorDebil::evaluaEjemplo(const vector<float> & xIntegralRenglon) const
{
	float feature;
	unsigned short i, j, k;
	
	if(plantilla.tipo == 0)
	{
		i = plantilla.inicio;
		j = plantilla.inicio + plantilla.tamano - 1;
		if(i==0)
			feature = xIntegralRenglon[j];
		else
			feature = xIntegralRenglon[j] - xIntegralRenglon[i-1];
	}
	else if(plantilla.tipo == 1)
	{
		i = plantilla.inicio;
		j = plantilla.inicio + plantilla.tamano - 1;
		k = j + plantilla.tamano;
		if(i==0)
			feature = xIntegralRenglon[j] - (xIntegralRenglon[k] - xIntegralRenglon[j-1]);
		else
			feature = (xIntegralRenglon[j] - xIntegralRenglon[i-1]) - (xIntegralRenglon[k] - xIntegralRenglon[j-1]);
	}
		
	switch(parametros.polaridad){
		case(1):if(feature >= parametros.umbral)
					return 1;
				else
					return -1;
		case(-1): if(feature < parametros.umbral)
					return 1;
				else
					return -1;
	}
    
    return 1;
}

short ClasificadorDebil::evaluaEjemplo(const vector<float> & xIntegralRenglon, const struct PlantillaHaar1D & tmpPlantilla, 
									struct ParamClasificador tmpParametros) const
{
	float feature;
	unsigned short i, j, k;
	
	if(tmpPlantilla.tipo == 0)
	{
		i = tmpPlantilla.inicio;
		j = tmpPlantilla.inicio + tmpPlantilla.tamano - 1;
		if(i==0)
			feature = xIntegralRenglon[j];
		else
			feature = xIntegralRenglon[j] - xIntegralRenglon[i-1];
	}
	else if(tmpPlantilla.tipo == 1)
	{
		i = tmpPlantilla.inicio;
		j = tmpPlantilla.inicio + tmpPlantilla.tamano - 1;
		k = j + tmpPlantilla.tamano;
		if(i==0)
			feature = xIntegralRenglon[j] - (xIntegralRenglon[k] - xIntegralRenglon[j-1]);
		else
			feature = (xIntegralRenglon[j] - xIntegralRenglon[i-1]) - (xIntegralRenglon[k] - xIntegralRenglon[j-1]);
	}
		
	switch(tmpParametros.polaridad){
		case(1):if(feature >= tmpParametros.umbral)
					return 1;
				else
					return -1;
		case(-1): if(feature < tmpParametros.umbral)
					return 1;
				else
					return -1;
	}
    
    return 1;
}

double ClasificadorDebil::calculaError(const vector< vector<float> > & xIntegral, const vector<short> & y, unsigned int numEjemplos,
									const struct PlantillaHaar1D & tmpPlantilla, struct ParamClasificador tmpParametros)
{
	double tmpError = 0.0;
	double factor = 0.0;
	
	for(unsigned int i=0; i<numEjemplos; i++)
	{
		if( y[i] == evaluaEjemplo(xIntegral[i], tmpPlantilla, tmpParametros) )
			factor = 0.0;
		else
			factor = 1.0;
		tmpError += distribucion[i]*factor;
	}
	
	return tmpError;
}

struct ParamClasificador ClasificadorDebil::seleccionaMejorCaracteristica(const vector< vector<float> > & xIntegral, const vector<short> & y, 
									const struct PlantillaHaar1D & tmpPlantilla)
{
		struct ParamClasificador tmpParametros, mejoresParametros;
		unsigned int numEjemplos = y.size();
		vector<float> features;
		
		unsigned short i, j, k;
		if(tmpPlantilla.tipo == 0)
		{
			i = tmpPlantilla.inicio;
			j = tmpPlantilla.inicio + tmpPlantilla.tamano - 1;
			for(unsigned int idx=0; idx<numEjemplos; idx++)
				if(tmpPlantilla.inicio == 0)
					features.push_back( xIntegral[idx][j] );
				else
					features.push_back( xIntegral[idx][j] - xIntegral[idx][i-1]);
		}
		else if(tmpPlantilla.tipo == 1)
		{
			i = tmpPlantilla.inicio;
			j = tmpPlantilla.inicio + tmpPlantilla.tamano - 1;
			k = j + tmpPlantilla.tamano;
			for(unsigned int idx=0; idx<numEjemplos; idx++)
				if(tmpPlantilla.inicio == 0)
					features.push_back( xIntegral[idx][j] - (xIntegral[idx][k] - xIntegral[idx][j-1]) );
				else
					features.push_back( (xIntegral[idx][j] - xIntegral[idx][i-1]) - (xIntegral[idx][k] - xIntegral[idx][j-1]) );
		}
		
		mejoresParametros.umbral = features[0];
		mejoresParametros.polaridad = 1;
		
		double tmpError;
		double menorError = 1.0;
		
		tmpParametros.polaridad = 1;
		for(unsigned int idx=0; idx<numEjemplos; idx++)
		{	
			tmpParametros.umbral = features[idx];
			tmpError = calculaError(xIntegral, y, numEjemplos, tmpPlantilla, tmpParametros);
			if(tmpError < menorError)
			{
				menorError = tmpError;
				mejoresParametros = tmpParametros;
			}
			if(menorError == 0) return mejoresParametros;
		}
		
		tmpParametros.polaridad = -1;
		for(unsigned int idx=0; idx<numEjemplos; idx++)
		{	
			tmpParametros.umbral = features[idx];
			tmpError = calculaError(xIntegral, y, numEjemplos, tmpPlantilla, tmpParametros);
			if(tmpError < menorError)
			{
				menorError = tmpError;
				mejoresParametros = tmpParametros;
			}
			if(menorError == 0) return mejoresParametros;
		}
		
		return mejoresParametros;
}
