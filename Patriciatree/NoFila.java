public class NoFila {
    No info;
    NoFila prox;

    public NoFila(No info) {
        this.info = info;
        this.prox = null;
    }

    public No getInfo() {
        return info;
    }

    public void setInfo(No info) {
        this.info = info;
    }

    public NoFila getProx() {
        return prox;
    }

    public void setProx(NoFila prox) {
        this.prox = prox;
    }
}
