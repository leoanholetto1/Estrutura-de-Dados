public class Arv implements Definicoes {
    private No raiz;

    private No localizarNo(int info) {
        No no=raiz;
        boolean achou = false;
        while(no != null && !achou) {
            int pos = no.buscaPos(info);
            if(pos < no.getTL() && no.getvInfo(pos) == info)
                achou = true;
            else
                no = no.getvLig(pos);
        }
        return no;
    }

    private No navegarAteFolha(int info) {
        int i;
        No aux = raiz;
        while(aux.getvLig(0) != null) {
            aux = aux.getvLig(aux.buscaPos(info));
        }
        return aux;
    }

    private No localizarPai(No folha, int info) {
        int i;
        No atu = raiz, ant = raiz;
        while(ant != folha) {
            i = atu.buscaPos(info);
            ant = atu;
            atu = atu.getvLig(i);
        }
        return ant;
    }

    public void insere(int info) {
        No folha, pai;
        if(raiz == null)
            raiz = new No(info);
        else {
            folha = navegarAteFolha(info);
            int pos = folha.buscaPos(info);
            folha.remaneja(pos);
            folha.setvInfo(pos,info);
            folha.setTL(folha.getTL() + 1);
            if(folha.getTL() == n) {
                pai = localizarPai(folha,info);
                split(folha,pai);
            }
        }
    }

    public void split(No folha, No pai) {
        No c1 = new No(), c2 = new No();
        int q,i,j;
        if(folha.getvLig(0) == null) {
            q = (int) Math.ceil((double)(n-1)/2);
            for(i = 0; i < q; i++) {
                c1.setvInfo(i,folha.getvInfo(i));
                c1.setTL(c1.getTL() + 1);
            }
            for(j = i; j < n; j++) {
                c2.setvInfo(j - i,folha.getvInfo(j));
                c2.setTL(c2.getTL() + 1);
            }
            pai.setTL(1);
            pai.setvLig(pai.getTL() -1, c1);
            pai.setvLig(pai.getTL(), c2);
            pai.setvInfo(0,c2.getvInfo(0));
        }
        else {
            q = (int) Math.ceil(n/2) - 1;
            for(i = 0; i < q; i++) {
                c1.setvInfo(i,folha.getvInfo(i));
                c1.setTL(c1.getTL() + 1);
            }
            pai.setTL(1);
            pai.setvInfo(0,folha.getvInfo(i++));
            for(j = i; j < n; j++) {
                c2.setvInfo(j - i,folha.getvInfo(j));
                c2.setTL(c2.getTL() + 1);
            }
            pai.setvLig(pai.getTL() -1, c1);
            pai.setvLig(pai.getTL(), c2);

        }
        c2.setProx(pai.getProx());
        pai.setProx(null);
        c1.setProx(c2);
        No aux = raiz;
        while(aux.getvLig(0) != null)
            aux = aux.getvLig(0);
        while(aux.getProx() != null && aux.getProx() != pai)
            aux = aux.getProx();
        if(aux.getProx() != null)
            aux.setProx(c1);

        if(pai.getTL() == n) {
            folha = pai;
            pai = localizarPai(folha,folha.getvInfo(0));
            split(folha,pai);
        }
    }

    public void exibeFolhas() {
        No aux = raiz;
        while(aux.getvLig(0) != null)
            aux = aux.getvLig(0);
        System.out.print("[ ");
        while(aux != null) {
            for (int i = 0; i < aux.getTL(); i++)
                System.out.print(aux.getvInfo(i) + " ");
            aux = aux.getProx();
        }
        System.out.println("]");
    }

    public void inOrdem() {
        inOrdem(raiz);
    }

    private void inOrdem(No raiz) {
        if(raiz != null) {
            for(int i = 0; i < raiz.getTL(); i++) {
                inOrdem(raiz.getvLig(i));
                System.out.println(raiz.getvInfo(i));
            }
            inOrdem(raiz.getvLig(raiz.getTL()));
        }
    }
}
