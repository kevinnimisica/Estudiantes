#include <iostream>
#include <string>
#include <string>
#include <stdlib.h>

using namespace std;

struct Sabana                   /*Se declara esta estructura de datos para guardar la sabana de cada estudiante
                                y como cualquier sabana tiene el codigo que caracteriza a la materia y el dato del
                                cual se sabe si la materia está aprobada o no.*/
{
    string codigoMateria;
    bool materiaAprobada;
};

struct Estudiante               /*Esta estructura de datos contiene todos los datos que necesita el sistema para cada estudiante
                                un entero que es el identificador de cada estudiante, una cadena de caracteres (string) que contiene
                                el nombre del estudiante, un valor decimal que guarde el promedio de cada estudiante, una matriz de 5*5
                                de tipo sabana para el pensum de cada estudiante, un boleano que indica si el estudiante ha solicitado
                                matrícula o no lo ha hecho, un vector de las materias que el estudiante quiere inscribir de 7 datos
                                porque lo maximo que se puede matricular son 21 créditos, un string del resultado de cada matrícula,
                                allí se guardan todos los problemas que se presentaron con la matrícula*/
{
    int codigoEstudiante;
    string nombreEstudiante;
    float promedio;
    Sabana materias[5][5];
    bool solicitudMatricula;
    string materiasParaInscribir[7] = { " " };
    string resultadoMatricula;
};

/*Esta es la sección en la que se declaran todas las funciones
que se usan a lo largo del programa, cada una será explicada en su definición*/

void MostrarMaterias(Estudiante[], int);
void OrdenarNombre(Estudiante[], int);
void ListarNoMatriculados(Estudiante[], int);
void OrdenarPorCodigo(Estudiante[], int);
void PublicarPermisos(Estudiante[], int);
void ConsultarDatos(Estudiante[], int);
bool Requisitos(string, Estudiante[], int, int);
bool permisosAsignaturas(Estudiante[],int,float);
bool Matricula(Estudiante[], int);
int ValidarCodigo(Estudiante[], int, int);
void LlenarMaterias(Estudiante[],int);
bool ValidarMateria(Estudiante[],string);
bool esEntero(string s);

int main()      /*Esta es la función principal en la cual se ingresan los datos de los estudiantes y se muestra el menú de opciones*/
{
    int cantidadEstudiantes, creditos,opcion;       /*Se declaran las variables necesarias, la cantidad de
                                                estudiantes para saber cuantos datos  del vector de estudiantes se deben recibir
                                                los créditos son la variable en la que se verifica qué se debe hacer, si llenar el
                                                año correspondiente o pedir las materias aprobadas*/
    string temp;                                /*este string es una variable temporal que va a ser evaluada en una función
                                                para saber si el dato que ha sido ingresado en la cantidad de estudiantes es un número o no lo es*/
    int codigoTemporal;                         //Esta es un codigo temporal para ser evaluado si el código que se esta ingresando ha sido ingresado amtesy evitar duplicación de ID
    Estudiante estudiantes[100];
    cout<<"*****************************************************************" << endl;
    cout<<"         **********************************************          " << endl;
    cout<<"         *       Universidad de las Am\202ricas       *          " << endl;
    cout<<"         **********************************************          " << endl;
    cout<<"****************************************************************" << endl;

    do  //EL ciclo se encarga de validar si el dato ingresado en la cantidad de estudiantes es digito, si no lo es, entonces se pide el dato de nuevo
    {
        cout<<"\nIngrese la cantidad actual de estudiantes en el sistema: ";
        cin>>temp;
    }
    while(!esEntero(temp));     //se llama la función que verifica que el dato este bien para ingresar
    cantidadEstudiantes = atoi(temp.c_str());//Se le asigna el valor del dato ingresado a la cantidad de estudiantes, pero, antes se hace la conversion de caracter a entero
    cantidadEstudiantes++;                   //Se ajusta la cantidad de estudiante poque la transformación lo dejó con un dijito menos
    cout<<"**************************************************************" << endl<<endl;
    LlenarMaterias(estudiantes,cantidadEstudiantes);    /*Se llama esta función la cual se encarga de llenar los codigos de las
                                                        materias en la sbana de la cantidad de estudiantes que hay en el sistema*/
    for(int i = 0 ; i < cantidadEstudiantes - 1 ; i++)
    {
        bool matriculada = false;                       //esta bandera se utiliza para saber si la materia se encontró en la matriz
        cin.ignore(256,'\n');                           //se utiliza esta función para limbiar el buffer y evitar fallos en el uso de getline
        cout<<"Nombre del estudiante " << i+1 << ": ";  //se muestra qué dat debe ingresar
        getline(cin,estudiantes[i].nombreEstudiante);   //se recibe el nombre completo con espacios con la función que viene implementada
        do
        {
            cout<<"C\242digo del estudiante " << estudiantes[i].nombreEstudiante << " (0-99999): ";
            cin>>codigoTemporal;
        }
        while (codigoTemporal < 0 || codigoTemporal > 99999 || ValidarCodigo(estudiantes,codigoTemporal,cantidadEstudiantes)!=-1);
        //el ciclo de la linea anterior se asegura que el codigo que se está ingresando no esté repetido y que no esté fuera del rango
        estudiantes[i].codigoEstudiante = codigoTemporal;   //una vez el código es correcto se asigna el código al estudiante

        do
        {
            cout<<"Promedio del estudiante " << estudiantes[i].nombreEstudiante << ": ";
            cin>>estudiantes[i].promedio;
        }
        while (estudiantes[i].promedio < 0 || estudiantes[i].promedio > 5);
        //este ciclo se encarga de recibir el promedio y verificar que esté en el rango
        int anio=0; //este es un contador que nos indica en qué año está ingresando materias el estudiante
        do
        {
            do
            {
                cout<<"Ingrese los cr\202ditos para el estudiante " << estudiantes[i].nombreEstudiante << ": ";
                cin>>creditos;
            }
            while(creditos % 3 != 0);   //este ciclo se asegura que la cantidad de créditos sean validos
            if (creditos == 15)         //cuando créditos aprobados es 15 se asume que son las materias del año del pensum y esa columna se aprueba
            {
                for (int k = 0; k < 5 ; k++)
                {
                    estudiantes[i].materias[k][anio].materiaAprobada = true ;
                }
            }
            else            //Cuando no son 15 créditos entonces se deben ingresar las materias aprobadas
                for (int l = 0 ; l < (creditos/3) ; l++)    //este ciclo realiza la cantidad de materias a las que petenezcan los creditos ingresados
                {
                    cout<<"C\242digo de la materia " << l+1 << " para inscribir del estudiante " << estudiantes[i].nombreEstudiante << ": ";//se muestra el número de la materia en la que va para evitar confusiones
                    cin>>estudiantes[i].materiasParaInscribir[l];
                    for (int m = 0 ; m < 5 ; m++ )  //se recorre la matriz para verificar si la materia está en el pensum
                        for ( int n = 0 ; n < 5 ; n++ )
                        {
                            if (estudiantes[i].materiasParaInscribir[l] == estudiantes[i].materias[m][n].codigoMateria)//si la encuentra , entonces la aprueba
                            {
                                estudiantes[i].materias[m][n].materiaAprobada = true;
                                matriculada = true;
                            }
                        }
                    if (matriculada==false)//que la bandera esté en false significa que no la entcontro entonces se le esta uno al ciclo para que reciba la materia que está mal ingesada
                            {
                                l--;
                            }
                }
            anio++;//se aumenta el año en el que el estudiante está ingresando materias
        }
        while( creditos != 0 && anio<=4);   //esto se repetirá hasta que se ingres un cero en los créditos o haya llenado los 5 años con materias aprobadas
    }
    do
    {
        cout<<endl<<"******************************************************"<<endl;
        cout<<"1) Ingresar solicitud de matr\241cula."<<endl;
        cout<<"2) Consultar datos del estudiante."<<endl;
        cout<<"3) Publicar permisos."<<endl;
        cout<<"4) Listar estudiantes que no han realizado solicutud de matr\241cula."<<endl;
        cout<<"5) Terminar."<<endl;
        do
        {
            cout<<"\nDigite la opci\242n:\t";
            cin>>opcion;
        }
        while(opcion<1||opcion>5);  //se evalua que la opción sea valida o si no se pide que la ingrese de nuevo
        //estos 4 if evaluan la opción y llaman las funciones que corresponden a la solción de lo que el usuario quiere ver
        if(opcion==1)
            Matricula(estudiantes,cantidadEstudiantes);
        if(opcion==2)
            ConsultarDatos(estudiantes,cantidadEstudiantes);
        if(opcion==3)
            PublicarPermisos(estudiantes,cantidadEstudiantes);
        if(opcion==4)
            ListarNoMatriculados(estudiantes,cantidadEstudiantes);
    }
    while(opcion!=5); //este ciclo se repite pidiendo la opción que quiere el usuarios hasta que utilice la opción 5 para terminar el programa
    return 0;
}


void MostrarMaterias(Estudiante estudiantes[], int posicion)//está función es muy básica,sólo recorre la matriz de materias buscando los curosos vistos en la posición que le fue entregada y si encuentra que la materia esta aprobada imprime el codigo
{
    for (int i = 0; i<5; i++)   //se repite 5 veces porque es la cantidad de filas de la matiz
    {
        for (int j = 0; j<5; j++)   //igualmente se repite 5 veces porque es la cantidad de columnas de la matriz
        {
            if (estudiantes[posicion].materias[i][j].materiaAprobada == true)
            {
                cout << estudiantes[posicion].materias[i][j].codigoMateria<<"  ";
            }
        }
    }
    cout << endl;
}

void OrdenarNombre(Estudiante estudiantes[], int cantidad)  //esta función es un ordenamiento tipo burbuja para que el vector de estudiantes se ordene por nombre
{
    Estudiante aux;
    for (int i = 0; i<cantidad; i++)
    {
        for (int j = 0; j<cantidad; j++)
        {
            if (estudiantes[i].nombreEstudiante<estudiantes[j].nombreEstudiante)
            {
                aux = estudiantes[i];
                estudiantes[i] = estudiantes[j];
                estudiantes[j] = aux;
            }
        }
    }
}

void ListarNoMatriculados(Estudiante estudiantes[], int cantidad)   //esta función lista los estudiantes que no han hecho solicutud de matrícula
{
    OrdenarNombre(estudiantes, cantidad);   //llama la función para que estén ordenados por nombre
    cout << "Los estudiantes que no han matriculado son: " << endl;
    for (int i = 0; i<cantidad; i++)    //el ciclo se repite la cantidad de veces que hay estudiantes en el vector
        if (estudiantes[i].solicitudMatricula == false) //si el dato está en falso signifca que no se ha solicitado matrícula, por lo tanto imprime todos los datos del estudiante
        {
            cout << "*************************************" << endl;
            cout << "Nombre: \t" << estudiantes[i].nombreEstudiante << endl;
            cout << "ID: \t " << estudiantes[i].codigoEstudiante << endl;
            cout << "Promedio: \t " << estudiantes[i].promedio << endl;
            cout << "Cursos vistos \n";
            MostrarMaterias(estudiantes, i);    //se llama la función para mostrar la sabana de materias aptrobadas por el estudiante
            cout << "**************************************";
        }
}

void OrdenarPorCodigo(Estudiante estudiantes[], int cantidad)   //este es otro ordenamiento de tipo burbuja que deja el vector de estudiantes ordenado por códigos
{
    Estudiante aux;
    for (int i = 0; i<cantidad; i++)
    {
        for (int j = 0; j<cantidad; j++)
        {
            if (estudiantes[i].codigoEstudiante<estudiantes[j].codigoEstudiante)
            {
                aux = estudiantes[j];
                estudiantes[j] = estudiantes[i];
                estudiantes[i]= aux;
            }
        }
    }
}

void PublicarPermisos(Estudiante estudiantes[], int cantidad)   //Esta es la opción tres, que se encarga de publicar el resultado de la matrícula de los estudiantes que la solicutaron
{
    OrdenarPorCodigo(estudiantes, cantidad);    //se llama la función apra que los estudiantes queden ordenados por código
    for (int i = 0; i<cantidad; i++)
    {
        if (estudiantes[i].solicitudMatricula)  //Si el dato esta en TRUE significa que el estudiante hizo solicitud de materia, entoces procede a imprimir los datos del estudiante más el resultado de la matrícula
        {
            cout << "********************************************" << endl;
            cout << "Nombre:\t" << estudiantes[i].nombreEstudiante << endl;
            cout << "ID:\t" << estudiantes[i].codigoEstudiante << endl;
            cout << "Promedio:\t" << estudiantes[i].promedio << endl;
            cout << "Cursos vistos:" << endl;
            MostrarMaterias(estudiantes, i);
            cout << "Matricul\242:\t";
            for (int j = 0; j<7; j++)
                cout << estudiantes[i].materiasParaInscribir[j];
            cout << "**********************************************" << endl;
            cout << estudiantes[i].resultadoMatricula;
        }
    }
}

int ValidarCodigo(Estudiante estudiantes[], int codigo, int cantidad)   //esta es una pequeña pero, muy útil función que se encarga de encontar al estudiante por su código y retorna la posición o el dato que indica que el estudiante no fue encontrado
{
    for (int i = 0; i<cantidad; i++)
    {
        if (estudiantes[i].codigoEstudiante == codigo)
        {
            return i;
        }
    }
    return -1;
}

void ConsultarDatos(Estudiante estudiantes[], int cantidad) //Esta función se encarga de la opción dos
{
    int codigo, posicion;
    do
    {
        cout << "********************************************" << endl;
        cout << "\nConsultar datos del estudiante:\n\n";
        cout << "Ingrese el c\242digo:\t";
        cin >> codigo;
        posicion = ValidarCodigo(estudiantes, codigo, cantidad);
    }
    while (posicion== -1); //este ciclo se encarga de encontar el estudiante, si no lo encuentra, entonces se pide el código nuevamente, al salir de este ciclo procede a imprimir todos los datos del estudiante
    cout << "\nNombre:\t" << estudiantes[posicion].nombreEstudiante << endl;
    cout << "ID:\t" << estudiantes[posicion].codigoEstudiante << endl;
    cout << "Promedio:\t" << estudiantes[posicion].promedio << endl;
    cout << "Cursos vistos:\t" ;
    MostrarMaterias(estudiantes, posicion);
    cout << "Matricul\242:\t" ;
    for (int i = 0; i<7; i++)   //este ciclo imprime las materias que el estudiante intentó matricular si las hay
    {
        cout << estudiantes[posicion].materiasParaInscribir[i]<<"  ";
    }
    cout << "\n" << endl;
}

bool Requisitos(string materia, Estudiante estudiantes[], int cantidad, int posicion)//esta función se encarga de verificar los requisitos para la matriculadependiendo de cada materia y sus requisitos correspondientes según el pensum
{
    if (materia == "M2")
    {
        if (estudiantes[posicion].materias[0][0].materiaAprobada)
            return true;
        else
            estudiantes[posicion].resultadoMatricula += " No tiene los requisitos para ver M2";
        return false;
    }
    else if (materia == "FP")
    {
        if (estudiantes[posicion].materias[1][0].materiaAprobada)
            return true;
        else
        {
            estudiantes[posicion].resultadoMatricula += " No tiene los requisitos para ver FP";
            return false;
        }
    }
    else if (materia == "M3")
    {
        if (estudiantes[posicion].materias[0][1].materiaAprobada)
            return true;
        else
        {
            estudiantes[posicion].resultadoMatricula += " No tiene los requisitos para ver M3";
            return false;
        }
    }
    else if (materia == "F1")
    {
        if (estudiantes[posicion].materias[0][2].materiaAprobada)
            return true;
        else
        {
            estudiantes[posicion].resultadoMatricula += " No tiene los requisitos para ver F1";
            return false;
        }
    }
    else if (materia == "HI")
    {
        if (estudiantes[posicion].materias[1][1].materiaAprobada)
            return true;
        else
        {
            estudiantes[posicion].resultadoMatricula += " No tiene los requisitos para ver HI";
            return false;
        }
    }
    else if (materia == "IC")
    {
        if (estudiantes[posicion].materias[1][2].materiaAprobada)
            return true;
        else
        {
            estudiantes[posicion].resultadoMatricula += " No tiene los requisitos para ver IC";
            return false;
        }
    }
    else if (materia == "PF")
    {
        if (estudiantes[posicion].materias[4][3].materiaAprobada)
            return true;
        else
        {
            estudiantes[posicion].resultadoMatricula += " No tiene los requisitos para ver PF";
            return false;
        }
    }
    else if (materia == "PS")
    {
        if (estudiantes[posicion].materias[2][1].materiaAprobada)
            return true;
        else
        {
            estudiantes[posicion].resultadoMatricula += " No tiene los requisitos para ver PS";
            return false;
        }
    }
    else if (materia == "SI")
    {
        if (estudiantes[posicion].materias[2][2].materiaAprobada)
            return true;
        else
        {
            estudiantes[posicion].resultadoMatricula += " No tiene los requisitos para ver SI";
            return false;
        }
    }
    else if (materia == "MD")
    {
        if (estudiantes[posicion].materias[4][1].materiaAprobada)
            return true;
        else
        {
            estudiantes[posicion].resultadoMatricula += " No tiene los requisitos para ver MD";
            return false;
        }
    }
    else if (materia == "CO")
    {
        if (estudiantes[posicion].materias[4][1].materiaAprobada)
            return true;
        else
        {
            estudiantes[posicion].resultadoMatricula += " No tiene los requisitos para ver CO";
            return false;
        }
    }
    else if (materia == "EC")
    {
        if (estudiantes[posicion].materias[4][2].materiaAprobada)
            return true;
        else
        {
            estudiantes[posicion].resultadoMatricula += " No tiene los requisitos para ver EC";
            return false;
        }
    }        /*Si la materia no esta entre estos significa que es una materia sin requisito por lo cual se retorna true, pero, si
            llegase a no cumplir una materia algún requisito, entonces se guarda el caso en el reporte del estudiante por lo cual no puede matricular*/
    else
        return true;
}

void LlenarMaterias(Estudiante estudiantes[],int cantidad)  //esta función se encarga de llenar la sabana de todos los estudiantes con las materias del pensum
{
    for(int i=0; i<cantidad; i++)
    {
        estudiantes[i].materias[0][0].codigoMateria="M1";
        estudiantes[i].materias[0][1].codigoMateria="M2";
        estudiantes[i].materias[0][2].codigoMateria="M3";
        estudiantes[i].materias[0][3].codigoMateria="F1";
        estudiantes[i].materias[0][4].codigoMateria="IC";
        estudiantes[i].materias[1][0].codigoMateria="ID";
        estudiantes[i].materias[1][1].codigoMateria="FP";
        estudiantes[i].materias[1][2].codigoMateria="HI";
        estudiantes[i].materias[1][3].codigoMateria="E1";
        estudiantes[i].materias[1][4].codigoMateria="PF";
        estudiantes[i].materias[2][0].codigoMateria="Q1";
        estudiantes[i].materias[2][1].codigoMateria="AL";
        estudiantes[i].materias[2][2].codigoMateria="PS";
        estudiantes[i].materias[2][3].codigoMateria="E2";
        estudiantes[i].materias[2][4].codigoMateria="SI";
        estudiantes[i].materias[3][0].codigoMateria="DB";
        estudiantes[i].materias[3][1].codigoMateria="DI";
        estudiantes[i].materias[3][2].codigoMateria="MD";
        estudiantes[i].materias[3][3].codigoMateria="E3";
        estudiantes[i].materias[3][4].codigoMateria="GE";
        estudiantes[i].materias[4][0].codigoMateria="L1";
        estudiantes[i].materias[4][1].codigoMateria="PE";
        estudiantes[i].materias[4][2].codigoMateria="CO";
        estudiantes[i].materias[4][3].codigoMateria="I2";
        estudiantes[i].materias[4][4].codigoMateria="EC";
    }
}

bool ValidarMateria(Estudiante estudiantes[],string materia)//Esta función se encarga de definir si una materia está en el pensum
{
    for(int i=0; i<5; i++)          //los dos ciclos son para recorrer la matriz en la que estan todos los códigos del pensum
        for(int j=0; j<5; j++)
        {
            if(estudiantes[0].materias[i][j].codigoMateria==materia)    //si encuentra la materia retorna true y se acaba la función
                return true;
        }
    return false;
}

bool permisosAsignaturas(Estudiante estudiantes [],int posicion,float opcion)   //esta función se ecarga de los permisos especiales
{
    if (opcion == 1 )   //la opción un corresponde a matricular menos de nueve créditos
    {
        int creditosGanados = 0;//se recorre la matriz acumulando la cantidad de créditos para determinar si es posible dar el permiso
        for (int j = 0 ; j < 5 ; j++)
            for (int k = 0 ; k < 5 ; k++)
                if (estudiantes[posicion].materias[j][k].materiaAprobada == true )
                    creditosGanados+=3;
        if (creditosGanados >= 60)
            return true;
        else
            estudiantes[posicion].resultadoMatricula+=" No tiene los suficientes cr\202ditos para matricular menos de nueve cr\202ditos";
        return false;
    }
    if (opcion == 2)    //la opcion dos corresponde a matricular más de 15 créditos
    {
        if (estudiantes[posicion].promedio > 4.2)   // se valida que el promedio esté por encima de 4.2 para conceder el permiso
            return true;
        else
            estudiantes[posicion].resultadoMatricula+=" No tiene el promedio suficiente para matricular m\240s de 15 cr\202ditos";
        return false;
    }
    if (opcion == 3.1)  //este es el caso de materias sin requisitos DI
    {
        if ((estudiantes[posicion].materias[1][0].materiaAprobada == true && estudiantes[posicion].materias[3][0].materiaAprobada== false) || (estudiantes[posicion].materias[1][0].materiaAprobada == false && estudiantes[posicion].materias[3][0].materiaAprobada== true)||(estudiantes[posicion].materias[1][0].materiaAprobada == true &&estudiantes[posicion].materias[3][0].materiaAprobada== true))
            return true;
        else
            estudiantes[posicion].resultadoMatricula+=" No es posible conceder el permiso para matricular DI";
        return false;
    }
    if (opcion == 3.2)  //este es el caso de materias sin requisitos GE
    {
        if ((estudiantes[posicion].materias[3][2].materiaAprobada == true && estudiantes[posicion].materias[4][2].materiaAprobada == false) || (estudiantes[posicion].materias[3][2].materiaAprobada == false && estudiantes[posicion].materias[4][2].materiaAprobada == true)||(estudiantes[posicion].materias[3][2].materiaAprobada == true && estudiantes[posicion].materias[4][2].materiaAprobada == true))
            return true;
        else
            estudiantes[posicion].resultadoMatricula+=" No es posible conceder el permiso para matricular GE";
        return false;
    }
    if (opcion == 4.1)  //este es el caso de electiva 1
    {
        if ((estudiantes[posicion].materias[1][1].materiaAprobada == true && estudiantes[posicion].materias[1][2].materiaAprobada == true) || ((estudiantes[posicion].materias[1][1].materiaAprobada == true) && estudiantes[posicion].materias[0][4].materiaAprobada == true) || ((estudiantes[posicion].materias[1][2].materiaAprobada == true) && estudiantes[posicion].materias[0][4].materiaAprobada == true))
            return true;
        else
            estudiantes[posicion].resultadoMatricula+=" No es posible conceder el permiso para matricular E1";
        return false;
    }
    if (opcion == 4.2)  //este es el caso de electiva 2
    {
        if ((estudiantes[posicion].materias[4][1].materiaAprobada == true && estudiantes[posicion].materias[4][2].materiaAprobada == true) || ((estudiantes[posicion].materias[4][1].materiaAprobada == true && estudiantes[posicion].materias[4][4].materiaAprobada == true) || ((estudiantes[posicion].materias[4][2].materiaAprobada == true && estudiantes[posicion].materias[4][4].materiaAprobada == true))))
            return true;
        else
            estudiantes[posicion].resultadoMatricula+=" No es posible conceder el permiso para matricular E2";
        return false;
    }
    if (opcion == 4.3)  //este es el caso de electiva 3
    {
        if ((estudiantes[posicion].materias[2][1].materiaAprobada == true && estudiantes[posicion].materias[2][2].materiaAprobada == true) || ((estudiantes[posicion].materias[2][1].materiaAprobada == true && estudiantes[posicion].materias[2][4].materiaAprobada == true) || ((estudiantes[posicion].materias[2][2].materiaAprobada == true && estudiantes[posicion].materias[2][4].materiaAprobada == true))))
            return true;
        else
            estudiantes[posicion].resultadoMatricula+=" No es posible conceder el permiso para matricular E3";
        return false;
    }
    bool materiastresanios = false;
    if (opcion == 5) //este es el caso de seminario  y se recorre la matriz para saber si tiene todos los primeros tres años aprobados y cumplir el requisito
    {
        for (int z = 0 ; z < 3 ; z++)
            for (int y = 0 ; y < 5 ; y++)

                if (estudiantes[posicion].materias[y][z].materiaAprobada ==true)
                    materiastresanios = true;
                else
                {
                    materiastresanios = false;
                    break;
                }
    }
    if (materiastresanios == false)
        return true;
    else
        estudiantes[posicion].resultadoMatricula+=" No es posible conceder el permiso para matricular I2";
    return false;
}

bool Matricula(Estudiante estudiantes[], int cantidad)
{
    int codigo, posicion, creditos;
    do
    {
        cout << "Ingrese el c\242digo:\t";
        cin >> codigo;
        posicion = ValidarCodigo(estudiantes, codigo, cantidad);
    }
    while (posicion == -1);
    estudiantes[posicion].solicitudMatricula=true;
    do
    {
        cout<<"Cu\240tos cr\202ditos desea matricular:\t";
        cin>>creditos;
    }
    while(creditos%3!=0||(creditos<=0&&creditos>21));
    if(creditos<=9) //se evalua la cantidad de créditos para saber si es un permiso  de menos de nueve créditos
    {
        permisosAsignaturas(estudiantes,posicion,1);
    }
    if (creditos>=15)   //se evalua la cantidad de créditos para saber si es un permiso  de más de 15 créditos
    {
        permisosAsignaturas(estudiantes,posicion,2);
    }

    for(int i=0; i<(creditos/3); i++)
    {
        cout<<"Ingrese la materia que desea inscribir:\t";
        cin>>estudiantes[posicion].materiasParaInscribir[i];
        if(ValidarMateria(estudiantes,estudiantes[posicion].materiasParaInscribir[i])==false)//se valida que la materia que se busca inscribir esté en el pensum
            i--;
    }
    for(int i=0; i<(creditos/3); i++)   //este ciclo se repite la cantidad de veces necesarias para recorre el vectode de las materias a inscribir
    {
        //se determina el caso de permiso especial, pero si no esninguno, entoces lo envia a requisitos de las demas materias
        if(estudiantes[posicion].materiasParaInscribir[i]=="DI")
            permisosAsignaturas(estudiantes,posicion,3.1);
        else if(estudiantes[posicion].materiasParaInscribir[i]=="GE")
            permisosAsignaturas(estudiantes,posicion,3.2);
        else if(estudiantes[posicion].materiasParaInscribir[i]=="E1")
            permisosAsignaturas(estudiantes,posicion,4.1);
        else if(estudiantes[posicion].materiasParaInscribir[i]=="E2")
            permisosAsignaturas(estudiantes,posicion,4.2);
        else if(estudiantes[posicion].materiasParaInscribir[i]=="E3")
            permisosAsignaturas(estudiantes,posicion,4.3);
        else if(estudiantes[posicion].materiasParaInscribir[i]=="I2")
            permisosAsignaturas(estudiantes,posicion,5);
        else
            Requisitos(estudiantes[posicion].materiasParaInscribir[i],estudiantes,cantidad,posicion);
    }
    if(estudiantes[posicion].resultadoMatricula==" ")   //si no hay nada en el reporte significa que se pudo matricular con exitp
    {
        estudiantes[posicion].resultadoMatricula="Se pudo matricular con exito.";
    }
}

bool esEntero(string s)
{
    for( unsigned i=0; i<s.length(); ++ i )
        if( s[i] < '0' || s[i] > '9' ) return false;
    return true;
}
