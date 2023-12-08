public class NArea implements Definicao{
    private No raiz;

    public NArea() {
        raiz = null;
    }

    public void inserir(int info){
        if(raiz==null){
            raiz = new No(info);
        }
        else{
            No p = raiz;
            int pos;
            boolean inseri=false;
            while(!inseri){
                pos = p.buscaPos(info);
                if(p.getTl() <  n){ //achei posição e tl<n
                    p.remanejar(pos);
                    p.setvInf(pos,info);
                    p.setTl(p.getTl()+1);
                    inseri = true;
                }
                else{
                    if(p.getvLig(pos)==null){ // achei a posição e ela ta null, ou seja, pode inserir
                        p.setvLig(pos, new No(info));
                        inseri = true;
                    }
                    else{ //anda para o prox no
                        p = p.getvLig(pos);
                    }
                }
            }
        }
    }

    public void excluir(No pai,int posPai,No no,int info){
        if(no==null){
            System.out.println("Não Encontrado!");
        }
        else{
            int pos = no.buscaPos(info);
            if(pos < no.getTl() && no.getvInf(pos)==info){
                if(no.getvLig(pos)==null && no.getvLig(pos+1)==null){
                    no.remanejarExclusao(pos);
                    no.setTl(no.getTl()-1);
                    if(no.getTl()==0){
                        if(no==raiz) raiz = null;
                        else{
                            pai.setvLig(posPai,null);
                        }
                    }
                }
                else{
                    if(no.getvLig(pos+1)!=null){
                        No sub = no.getvLig(pos+1);
                        int aux = sub.getvInf(0);
                        sub.setvInf(0,no.getvInf(pos));
                        no.setvInf(pos,aux);
                        excluir(no,pos+1,no.getvLig(pos+1),info);
                    }
                    else{
                        No sub = no.getvLig(pos);
                        int aux = sub.getvInf(sub.getTl()-1);
                        sub.setvInf(sub.getTl()-1,no.getvInf(pos));
                        no.setvInf(pos,aux);
                        excluir(no,pos,no.getvLig(pos),info);
                    }
                }
            }
            else{
                excluir(no,pos,no.getvLig(pos),info);
            }
        }
    }

    public void exclusao(int info){
        excluir(null,0,raiz,info);
    }

    public void exibe(No no){
        if(no==null) return ;
        for(int i=0;i<no.getTl();i++){
            exibe(no.getvLig(i));
            System.out.println(no.getvInf(i));
        }
        exibe(no.getvLig(no.getTl()));
    }

    public void exibe(){
        exibe(raiz);
    }
}
