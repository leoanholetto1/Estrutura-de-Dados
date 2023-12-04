public class No {

    private String info;
    private boolean terminal;
    private No[] vLig;

    public No() { this.vLig = new No[26]; terminal = false; }
    public No(String info) { this.info = info; terminal = false; this.vLig = new No[26]; }

    public No(String info, boolean terminal) {
        this.info = info;
        this.terminal = terminal;
        this.vLig = new No[26];
    }

    public String getInfo() {
        return info;
    }

    public void setInfo(String info) {
        this.info = info;
    }

    public boolean isTerminal() {
        return terminal;
    }

    public void setTerminal(boolean terminal) {
        this.terminal = terminal;
    }

    public No getvLig(int pos) {
        return vLig[pos];
    }

    public void setvLig(int pos, No no) {
        this.vLig[pos] = no;
    }
}
