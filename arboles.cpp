#include <iostream>

using namespace std;

template <class T>
class Arbol;

template <class T>
class Nodo {
	private:
	    T elem;
	    Nodo<T>* der;
	    Nodo<T>* izq;
	public:
	    Nodo() :elem(), izq(nullptr), der(nullptr) {};
	    friend class Arbol<T>;
};

template <class T>
class Arbol {
	private:
    public:
    	Nodo<T>* raiz;
    	Arbol() :raiz(nullptr){};
    	Nodo<T>* obtRaiz(){
    		return raiz;
		}
    	
    	void inicializa();
    	bool vacio();
		T recupera(Nodo<T>* pos);
    	void inserta(Nodo<T>* arbol, T elem);
    	Nodo<T>* localiza(Nodo<T>* arbol, T elem);
    	Nodo<T>* menor(Nodo<T>* arbol);
    	Nodo<T>* mayor(Nodo<T>* arbol);
    	bool es_hoja(Nodo<T>* arbol);
    	void recorrido_preorder(Nodo<T>* arbol);
    	void recorrido_inorder(Nodo<T>* arbol);
    	void recorrido_postorder(Nodo<T>* arbol);
    	void elimina(Nodo<T>* arbol, Nodo<T>* pos);
		int altura(Nodo<T>* arbol);
		int fact_eq(Nodo<T>* arbol);
		void balanceo();
		void rot_sim_izq(Nodo<T>* arbol);
		void rot_sim_der(Nodo<T>* arbol);
		void rot_dbl_izq(Nodo<T>* arbol);
		void rot_dbl_der(Nodo<T>* arbol);
};

template <class T>
void Arbol<T>::inicializa() {
    raiz = nullptr;
}

template <class T>
bool Arbol<T>::vacio() {
    return raiz == nullptr ? true : false;
}

template <class T>
T Arbol<T>::recupera(Nodo<T>* pos){
	if(raiz == nullptr || pos == nullptr){
		cout<<"Error de excepcion! Insuficiencia de datos"<<endl;
		return 0;
	}
	return pos->elem;
}

template <class T>
void Arbol<T>::inserta(Nodo<T>* arbol, T elem){
    if(arbol == nullptr){
        Nodo<T>* aux = new Nodo<T>;
        aux->elem = elem;
        arbol = aux;
    }else{
        if(elem < arbol->elem){
            inserta(arbol->izq, elem);
        }else{
            inserta(arbol->der, elem);
        }
    }
}

template <class T>
Nodo<T>* Arbol<T>::localiza(Nodo<T>* arbol, T elem){
    if(arbol == nullptr){
        return nullptr;
    }else if(elem == arbol->elem){
        return arbol;
    }else if(elem < arbol->elem){
        return localiza(arbol->izq, elem);
    }else{
        return localiza(arbol->der, elem);
    }
}

template <class T>
Nodo<T>* Arbol<T>::menor(Nodo<T>* arbol) {
    if(arbol == nullptr){
        return nullptr;
    }
    else{
        if(arbol->izq == nullptr){
            return arbol;
        }else{
            return menor(arbol->izq);
        }
    }
}


template <class T>
Nodo<T>* Arbol<T>::mayor(Nodo<T>* arbol){
    if(arbol == nullptr){
        return nullptr;
    }
    else{
        if(arbol->der == nullptr){
            return arbol;
        }else{
            return mayor(arbol->der);
        }
    }
}

template <class T>
bool Arbol<T>::es_hoja(Nodo<T>* arbol){
    if(arbol == nullptr){
        return false;
    }
    if(arbol->izq == nullptr && arbol->der == nullptr){
        return true;
    }else{
        return false;
    }
}

template <class T>
void Arbol<T>::recorrido_preorder(Nodo<T>* arbol){
    if(arbol == nullptr){
        return;
    }

    cout<<arbol->elem<<endl;
    recorrido_preorder(arbol->izq);
    recorrido_preorder(arbol->der);
}

template <class T>
void Arbol<T>::recorrido_inorder(Nodo<T>* arbol){
    if(arbol == nullptr){
        return;
    }

    recorrido_inorder(arbol->izq);
    cout<<arbol->elem<<endl;
    recorrido_inorder(arbol->der);
}

template <class T>
void Arbol<T>::recorrido_postorder(Nodo<T>* arbol){
    if (arbol == nullptr) {
        return;
    }

    recorrido_postorder(arbol->izq);
    recorrido_postorder(arbol->der);
    cout << arbol->elem << endl;
}

template <class T>
void Arbol<T>::elimina(Nodo<T>* arbol, Nodo<T>* pos){
    if(arbol == nullptr || pos == nullptr){
        cout<<"Este es el mensaje de error..."<<endl;
        return;
    }

    if(es_hoja(pos)){
        delete pos;
        pos = nullptr;
    }else{
        Nodo<T>* pos_reemplazo = nullptr;

        if(arbol->izq != nullptr){
            pos_reemplazo = mayor(arbol->izq);
        }else{
            pos_reemplazo = menor(arbol->der);
        }

        pos->elem = pos_reemplazo->elem;
        elimina(arbol, pos_reemplazo);
    }
}

template <class T>
int Arbol<T>::altura(Nodo<T>* arbol){
    if(arbol == nullptr){
        return 0;
    }else{
        int alt_izq = altura(arbol->izq);
        int alt_der = altura(arbol->der);

        if(alt_izq > alt_der) {
            return alt_izq + 1;
        }else{
            return alt_der + 1;
        }
    }
}

template <class T>
int Arbol<T>::fact_eq(Nodo<T>* arbol){
    if(arbol == nullptr){
        return 0;
    }else{
       return altura(arbol->der) - altura(arbol->izq);
    }
}

template <class T>
void Arbol<T>::balanceo(){
    if(fact_eq(raiz) < -1){
        if (fact_eq(raiz->izq) == -1){
            rot_sim_der(raiz);
        }else{
            rot_dbl_der(raiz);
        }
        return;
    }

    if(fact_eq(raiz) > 1){
        if (fact_eq(raiz->izq) == 1) {
            rot_sim_izq(raiz);
		}else{
            rot_dbl_izq(raiz);
        }
        return;
    }
}

template <class T>
void Arbol<T>::rot_sim_der(Nodo<T>* arbol){
    Nodo<T>* aux1 = arbol->izq;
    Nodo<T>* aux2 = arbol->izq->der;
    arbol->izq = aux2;
    aux1->der = arbol;
    arbol = aux1;
}

template <class T>
void Arbol<T>::rot_sim_izq(Nodo<T>* arbol){
    Nodo<T>* aux1 = arbol->der;
    Nodo<T>* aux2 = arbol->der->izq;
    arbol->der = aux2;
    aux1->izq = arbol;
    arbol = aux1;
}

template <class T>
void Arbol<T>::rot_dbl_der(Nodo<T>* arbol){
    Nodo<T>* aux1 = arbol->izq;
    Nodo<T>* aux2 = aux1->der;
    Nodo<T>* aux3 = aux2->izq;
    Nodo<T>* aux4 = aux2->der;
    arbol->izq = aux4;
    aux1->der = aux3;
    aux2->izq = aux1;
    arbol = aux2;
}

template <class T>
void Arbol<T>::rot_dbl_izq(Nodo<T>* arbol){
    Nodo<T>* aux1 = arbol->der;
    Nodo<T>* aux2 = aux1->izq;
    Nodo<T>* aux3 = aux2->der;
    Nodo<T>* aux4 = aux2->izq;
    arbol->der = aux4;
    aux1->izq = aux3;
    aux2->der = aux1;
    arbol = aux2;
}

int main(){
	Arbol<int> arbol;  
    
	return 0;
}