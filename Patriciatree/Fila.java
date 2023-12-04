public class Fila {
    NoFila ini,fim;

    public Fila() {
        ini = fim = null;
    }

    public void push(No no){
        NoFila novo = new NoFila(no);
        if(ini==null){
            ini = fim = novo;
        }
        else{
            fim.setProx(novo);
            fim = novo;
        }
    }

    public boolean isEmpty(){
        return ini==null;
    }

    public No pop(){
        NoFila aux = ini;
        ini = ini.getProx();
        return aux.getInfo();
    }
}
