public class No implements Definicao{
    private int vInf[] = new int[n];
    private No vLig[] = new No[n+1];
    private int tl;

    public No() {
        this.tl = 0;
    }
    public No(int info) {
        this.vInf[0] = info;
        this.tl = tl + 1;
    }

    public void setvInf(int pos,int info){
        this.vInf[pos] = info;
    }

    public int getvInf(int pos){
        return this.vInf[pos];
    }

    public void setvLig(int pos,No info){
        this.vLig[pos] = info;
    }

    public No getvLig(int pos){
        return this.vLig[pos];
    }

    public void remanejar(int pos){
        for(int i=tl; i>pos;i--){
            vInf[i] = vInf[i-1];
            vLig[i] = vLig[i-1];
        }
    }

    public int buscaPos(int info){
        int i=0;
        while (i<tl && info > vInf[i]) i++;
        return i;
    }

    public int getTl() {
        return tl;
    }

    public void setTl(int tl) {
        this.tl = tl;
    }

    public void remanejarExclusao(int pos){
        for(int i=pos;i<tl-1;i++){
            vInf[i] = vInf[i+1];
            vLig[i] = vLig[i+1];
        }
        vLig[tl-1] = vLig[tl];
        vLig[tl] = null;
    }
}
