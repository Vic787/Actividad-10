/*
	Crear un programa que le solicite al usuario ingresar N cantidad de estudiantes (id, nombres, apellidos,
	nota1, nota2, nota3, nota4) y que calcule automáticamente el promedio y si la nota es superior a 60 que
	indique que el estudiante aprobó caso contrario que indique que reprobó, todo esto por medio de punteros
	o arreglos, utilice estructuras y cuando el usuario confirme que ya no desea ingresar más registros el 
	programa deberá de almacenar (id, nombres, apellidos, nota2, nota2, nota3, nota4, promedio, resultado)
	en un archivo binario llamado notas.dat todas las notas que el usuario asignó. Se debe crear el CRUD.
*/

#include <iostream>

using namespace std;

const char *nombre_archivo = "notas.dat";

struct Estudiante{
	int codigo[50];
	string nombres[50];
	string apellidos[50];
	int nota[4];
	float promedio[4];
};

void Crear();
void Leer();
void Actualizar();
void Borrar();

main(){
	Leer();
	Crear();
	Borrar();
	Actualizar();
	system("Pause");
}

void Leer(){
	system("cls");
	FILE* archivo = fopen(nombre_archivo, "rb");
	
	if(!archivo){
		archivo = fopen(nombre_archivo, "w+b");
	}
	
	Estudiante estudiante;
	int id = 0; // Indice o posición del registro (fila) dentro del archivo
	fread(&estudiante, sizeof(Estudiante), 1, archivo);
	cout << "__________________________________________________" << endl;
	cout << "ID  " << "|" << " Codigo "<< " | " << " Nombres " << "|"<< " Apellidos " << "|" << " Promedio" << endl;
	
	do{
		cout << id << " | " << estudiante.codigo << " | " << estudiante.nombres << " | " << estudiante.apellidos << " | " << estudiante.promedio << endl;
		fread(&estudiante, sizeof(Estudiante), 1, archivo);
		id+=1;
	}while(feof(archivo) == 0);
	
	fclose(archivo);
}

void Crear(){
	FILE* archivo = fopen(nombre_archivo, "a+b");
	
	char res;
	Estudiante estudiante;
	
	int notas = 0, n;
	
	cout << "Ingrese cuantos estudiantes desea ingresar: ";
	cin >> n;
	
	for(int i = 0; i < n; i++){
		notas = 0;
		cout << "--- Estudiante " << i+1 << " ---" << endl;
		cout << "____________________" << endl;
		
		cout << "Ingrese codigo: ";
		cin >> estudiante.codigo[i];
		cin.ignore();
		
		cout << "Ingrese nombres: ";
		getline(cin,estudiante.nombres[i]);
		
		cout << "Ingrese apellidos: ";
		getline(cin,estudiante.apellidos[i]);
		
		for(int ii = 0; ii < 4; ii++){
			cout << "Ingrese nota [" << ii+1 << "]: ";
			cin >> estudiante.nota[ii];
			notas += estudiante.nota[ii];
			fwrite(&estudiante, sizeof(Estudiante), 1, archivo);
		}
		
		estudiante.promedio[i] = notas/4;
		cout << "____________________" << endl;
	}
	
	cout << "Desea ingresar otro estudiante (s/n): ";
	cin >> res;
	
	while(res=='s' || res == 'S'){
		fflush(stdin);
		
		for(int i = 0; i < 1; i++){
			cout << "Ingrese codigo: ";
			cin >> estudiante.codigo[i];
			cin.ignore();
			
			cout << "Ingrese nombres: ";
			getline(cin,estudiante.nombres[i]);
			
			cout << "Ingrese apellidos: ";
			getline(cin,estudiante.apellidos[i]);
			
			for(int ii = 0; ii < 4; ii++){
				cout << "Ingrese nota [" << ii+1 << "]: ";
				cin >> estudiante.nota[ii];
				notas += estudiante.nota[ii];
				fwrite(&estudiante, sizeof(Estudiante), 1, archivo);
			}
			
			estudiante.promedio[i] = notas/4;
			cout << "____________________" << endl;
		}
		
		cout << "Desea ingresar otro estudiante (s/n): ";
		cin >> res;
	}
	
	fclose(archivo);
	Leer();
}

void Actualizar(){
	FILE* archivo = fopen(nombre_archivo, "r+b"); // Crea 
	Estudiante estudiante;
	int id = 0;
	
	cout << "Ingrese el ID que desea modificar: ";
	cin >> id;
	fseek(archivo, id * sizeof(Estudiante), SEEK_SET);
	
	for(int i = 0; i < 1; i++){
		fflush(stdin);
		cout << "Ingrese codigo: ";
		cin >> estudiante.codigo[i];
		cin.ignore();
		
		// Para el error "no matching function for call to 'std::basic_istream<char>::getline()' usar:
		// en vez de cin.getline(estudiante.nombre,50) usar getline(cin,estudiante.nombres[i])
		// Este error tira como 20 más pero así fácilmente se corrige
		cout << "Ingrese nombres: ";
		getline(cin,estudiante.nombres[i]);
			
		cout << "Ingrese apellidos: ";
		getline(cin,estudiante.apellidos[i]);
			
		fwrite(&estudiante, sizeof(Estudiante), 1, archivo);
	}
	
	fclose(archivo);
	Leer();
}

void Borrar(){
	const char *nombre_archivo_temp = "archivo_temp.dat";
	FILE* archivo = fopen(nombre_archivo,"rb");
	FILE* archivo_temp = fopen(nombre_archivo_temp,"w+b");
	Estudiante estudiante;
	
	int id = 0, id_n = 0;
	
	cout << "Ingrese el ID a eliminar: ";
	cin >> id;
	
	while(fread(&estudiante, sizeof(Estudiante), 1, archivo)){
		if(id_n != id){
			fwrite(&estudiante, sizeof(Estudiante), 1, archivo_temp);
		}
		id_n++;
	}
	
	fclose(archivo);
	fclose(archivo_temp);
	
	archivo_temp = fopen(nombre_archivo_temp,"rb");
	archivo = fopen(nombre_archivo,"wb");
	
	while(fread(&estudiante, sizeof(Estudiante), 1, archivo_temp)){
		fwrite(&estudiante, sizeof(Estudiante), 1, archivo);
	}
	
	fclose(archivo);
	fclose(archivo_temp);
	Leer();
}
