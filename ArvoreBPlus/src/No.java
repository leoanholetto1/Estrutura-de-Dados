public class No implements Definicoes {
    private No vLig[];
    private No prox;
    private int vInfo[];
    private int TL;

    public No(int info) {
        vLig = new No[n + 2];
        vInfo = new int[n + 1];
        vInfo[0] = info;
        TL = 1;
    }

    public No() {
        vLig = new No[n + 1];
        vInfo = new int[n + 2];
        TL = 0;
    }

    public No getvLig(int pos) {
        return vLig[pos];
    }

    public void setvLig(int pos,No lig) {
        this.vLig[pos] = lig;
    }

    public No getProx() {
        return prox;
    }

    public void setProx(No prox) {
        this.prox = prox;
    }

    public int getvInfo(int pos) {
        return vInfo[pos];
    }

    public int getTL() {
        return TL;
    }

    public void setTL(int TL) {
        this.TL = TL;
    }

    public void setvInfo(int pos, int info) {
        this.vInfo[pos] = info;
    }

    public void remaneja(int pos) {
        int i;
        vLig[TL + 1] = vLig[TL];
        for(i = TL; i > pos; i--) {
            vInfo[i] = vInfo[i - 1];
            vLig[i] = vLig[i - 1];
        }
    }

    public int buscaPos(int info) {
        int pos = 0;
        while(pos < TL && vInfo[pos] < info)
            pos++;
        return pos;
    }
}
