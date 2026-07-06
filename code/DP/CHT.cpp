//encontrar o max(f(x)) pra todo x
const int inf = 1e9;

struct line{
    int a,b;
    int right_x;
};

int intersection(line i,line j){ //encontrando o x que intersecta(em ints)
    int num=j.b-i.b;
    int den = i.a-j.a;
    return num / den - ((num^den)<0 &&  num % den); //ajeitando o floor pros negativos
}


vector<line> cht;

void insert_line(int a, int b){

    //tratando paralelas
    if(!cht.empty() && cht.back().a==a){
        if(cht.back().b>=b)return;
        cht.pop_back();
    }

    line l={a,b,inf};
    while(cht.size()>=2){
        int x1 = intersection(cht[cht.size()-2], cht[cht.size()-1]);
        int x2 = intersection(cht[cht.size()-1],l);
        if(x1>=x2){//nova reta superou totalmente a anterior melhor
            cht.pop_back();
        }
        else break;
    }

    if(!cht.empty()){
        cht.back().right_x = intersection(cht.back(),l);
    }
    cht.push_back(l);
}

bool slope_ord(line i, line j){
    return i.a<j.a;
}

void build_cht(vector<line> &v){
    sort(v.begin(),v.end(),slope_ord);
    for(auto el:v){
        insert_line(el.a,el.b);
    }
}

int query_max(int x){
    int i=-1;

    int low = 0, high = cht.size() - 1;
    while(low<=high){
        int mid = (low+high)/2;

        if(x<=cht[mid].right_x){
            i=mid;
            high = mid-1;
        } else{
            low = mid+1;
        }
    }

    return cht[i].a*x+cht[i].b;//aqui, to retornando o max(f(X))
    /*
    line = {cht[i].a,cht[i].b}
    return line  para retornar as linhas
    */
}