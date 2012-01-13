#ifndef METEO_H
#define METEO_H

#include <cstdlib>
#include <string>

class Meteo {
	public:
		Meteo();
		virtual ~Meteo();
		
		void download(std::string ville);
		void parse(std::string ville);
	
	private:
		
};

#endif
