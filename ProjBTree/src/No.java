public class No implements Definicoes {
    private int vInfo[];
    private int vPos[];
    private No vLig[];
    private int tl;

    public No() {
        vInfo = new int[2*m+1];
        vPos = new int[2*m+1];
        vLig = new No[2*m+2];
        tl = 0;
    }

    public No(int info, int posArq) {
        this();
        vInfo[0] = info;
        vPos[0] = posArq;
        tl = 1;
    }

    public int buscarPosicao(int info) {
        int pos=0;
        while(pos<tl && info>vInfo[pos])
            pos++;
        return pos;
    }

    public void remanejar(int pos) {
        vLig[tl+1] = vLig[tl];
        for(int i=tl; i>pos; i--)
        {
            vInfo[i] = vInfo[i-1];
            vPos[i] = vPos[i-1];
            vLig[i] = vLig[i-1];
        }
    }

    public void remanejarExclusao(int pos) {
        for(int j =pos; j < tl - 1; j++) {
            vInfo[j] = vInfo[j + 1];
            vPos[j] = vPos[j + 1];
            vLig[j] = vLig[j + 1];
        }
        vLig[tl - 1] = vLig[tl];
    }

    public int getvInfo(int p) {
        return vInfo[p];
    }

    public void setvInfo(int p, int info) {
        vInfo[p] = info;
    }

    public int getvPos(int p) {
        return vPos[p];
    }

    public void setvPos(int p, int pos) {
        vPos[p] = pos;
    }

    public No getvLig(int p) {
        return vLig[p];
    }

    public void setvLig(int p, No lig) {
        vLig[p] = lig;
    }

    public int getTl() {
        return tl;
    }

    public void setTl(int tl) {
        this.tl = tl;
    }

    public int procurarPosicao(int info) {
        int i = 0;
        while(i < tl && vInfo[i] < info)
            i++;
        return i;
    }
}
