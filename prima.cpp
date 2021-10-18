#include<iostream>

using namespace std;


struct lista{
    lista *next;
    int value, repr;
};

struct krawedz{
    krawedz *next, *prev;
    int v1, v2, waga;
};

int v1, v2, waga, v, e;
lista *p, *q, *k , **A;
krawedz *edges, *edge, *pedges, *kedges, *pfifo, *kfifo, *fifo;

void make_set(int i){	
    p = new lista;		
    p->value = i;      
    p->next = A[i];
    p->repr = i;    
    A[i] = p;
}

int find_set(int val){
    lista *tmp;
    
    for(int i=0;i<v;i++){
        tmp = A[i];
        while(tmp){
            if(tmp->value == val){
                return tmp->repr;
            }
            tmp = tmp->next;
        }    
    }
    cout<<endl;
    return 0;
}

void union_sets(int num, int num1){
    lista *lis, *lis1;
    lis1 = A[find_set(num1)];
    lis = A[find_set(num)];
    while(lis->next){
        lis = lis->next;
    }
    lis->next = lis1;

    if(A[lis1->value]){
        A[lis1->value] = NULL;
    }
    
    while(lis1){
        lis1->repr = lis->repr;
        lis1 = lis1->next;
    }
}

void prima(int start){
    cout<<"\nKrawedzie MST:"<<endl;
    pedges = edges;
    while(edges->v1 != start){
        edges= edges->next;
    }
    fifo = new krawedz;
    fifo->next = NULL;
    fifo->prev = NULL;
    fifo->v1 = edges->v1;
    fifo->v2 = edges->v2;
    fifo->waga = edges->waga;
    pfifo = kfifo = fifo;
    
    while(edges->v1 == start){
        fifo = new krawedz;
        fifo->next = NULL;
        fifo->prev = NULL;
        fifo->v1 = edges->v1;
        fifo->v2 = edges->v2;
        fifo->waga = edges->waga;
        if(fifo->waga <= pfifo->waga){
            fifo->next = pfifo;
            pfifo->prev = fifo;
            pfifo = fifo;
        }else{
            
        }

    }
}

int main(){
    cout<<"Podaj liczbe wierzcholkow i krawedzi."<<endl;
    cin>>v>>e;

    A = new lista * [v];

    edges = NULL;

    for(int i = 0; i < v; i++) A[i] = NULL;

    for(int i = 0; i < v; i++){
        make_set(i);
    }

    cout<<"Podaj krawedzie wraz z wagami."<<endl;
    cin>>v1>>v2>>waga;
    edge = new krawedz;
    edge->v1 = v1;
    edge->v2 = v2;
    edge->waga = waga;

    edge->next = edges;
    edge->prev = edges;

    edges = edge;
    pedges = kedges = edges;

    for(int i=0;i<e-1;i++){
        cin>>v1>>v2>>waga;
        edge = new krawedz;
        edge->v1 = v1;
        edge->v2 = v2;
        edge->waga = waga;
        //cout<<"przed pointerami"<<endl;
        if(edge->waga <= pedges->waga){
            //cout<<"if "<<endl;
            edge->next = pedges;
            edge->prev = NULL;
            pedges->prev = edge;
            pedges = edge;
        }else{
            //cout<<"else "<<endl;
            edges = pedges;
            while(edges){
                //cout<<"while"<<endl;
                if(edges->waga < edge->waga){
                    //cout<<"waga edges "<<edges->waga<<endl;
                    edges = edges->next;
                }else{
                    break;
                }    
            }
            //cout<<"po while"<<endl;
            if(edges){
                //cout<<"if po while "<<edges->waga<<endl;
                //cout<<"edges prev "<<edges->prev->waga<<endl;
                //cout<<"edges prev next "<<edges->prev->next->waga<<endl;
                edge->next = edges;
                edge->prev = edges->prev;
                (edges->prev)->next = edge;
                edges->prev = edge;
                //cout<<"edges prev "<<edges->prev->waga<<endl;
                //cout<<"edges prev next "<<edges->prev->next->waga<<endl;
                
            }else{
                //cout<<"else po while"<<kedges->waga<<endl;
                edge->next = NULL;
                edge->prev = kedges;
                kedges->next = edge;
                kedges = edge;
            }
        }        
    }
    
    //wypisuje krawedzie
    /*int i=1;
    while(pedges){
        cout<<"krawedz "<<i<<": ";
        cout<<pedges->v1<<" do "<<pedges->v2<<" waga "<<pedges->waga<<endl;
        pedges = pedges->next;
        i++;
    }*/

    
    prima(2);
    
    int i=1;
    while(pfifo){
        cout<<"krawedz "<<i<<": ";
        cout<<pfifo->v1<<" do "<<pfifo->v2<<" waga "<<pfifo->waga<<endl;
        pfifo = pfifo->next;
        i++;
    }

    /*
    // Wypisujemy zawartość tablicy list sąsiedztwa
    cout << endl;
    for(int i = 0; i < v; i++){
        cout << "A[" << i << "] = ";
        p = A[i];
        if(p){
            cout << p->repr<<": ";
        }
        
        while(p){
            cout.width(3);
            cout << p->value;
            p = p->next;
        }
        cout << endl;
    }*/
}