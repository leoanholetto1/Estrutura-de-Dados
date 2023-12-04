import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;

public class Patriciatree {
    private No raiz = null;

    ArrayList<String> palavras = new ArrayList<>();

    public Patriciatree() { }
    public No getRaiz() { return raiz; }
    public void setRaiz(No raiz) { this.raiz = raiz; }

    public ArrayList<String> getPalavras() {
        return palavras;
    }

    public void setPalavras(ArrayList<String> palavras) {
        this.palavras = palavras;
    }

    public void inserir(String info) {

        if(raiz == null) {
            raiz = new No("");
        }

        No no=raiz.getvLig(info.charAt(0)-'a'),pai=raiz;
        int i=0,j = 0;
        boolean flag=true;
        while(i< info.length() && no!=null && flag){
            j=0;
            while(i<info.length() && j<no.getInfo().length() && info.charAt(i)==no.getInfo().charAt(j)){
                j++;
                i++;
            }
            if(i < info.length()){
                if(j==no.getInfo().length()){
                    pai = no;
                    no = no.getvLig(info.charAt(i)-'a');
                }
                else{
                    if(info.charAt(i)!=no.getInfo().charAt(j)) flag=false;
                }
            }

        }

        if(no==null){
            pai.setvLig(info.charAt(i)-'a',new No(info.substring(i),true));
        }
        else {
            if (j == no.getInfo().length() && i == info.length()) {
                no.setTerminal(true);
            } else {
                if(i==info.length()) {
                    No novo  = new No(no.getInfo().substring(j), no.isTerminal());
                    for(int x=0;x<26;x++) {
                        novo.setvLig(x, no.getvLig(x));
                        no.setvLig(x,null);
                    }
                    no.setvLig(novo.getInfo().charAt(0)-'a',novo);
                    no.setInfo(no.getInfo().substring(0,j));
                    no.setTerminal(true);
                }
                else {
                    No noesq = new No(info.substring(i), true);
                    No nodir = new No(no.getInfo().substring(j),no.isTerminal());
                    no.setInfo(no.getInfo().substring(0,j));
                    no.setTerminal(false);
                    for(int k=0;k<26;k++){
                        nodir.setvLig(k,no.getvLig(k));
                        no.setvLig(k,null);
                    }
                    no.setvLig(noesq.getInfo().charAt(0)-'a',noesq);
                    no.setvLig(nodir.getInfo().charAt(0)-'a',nodir);
                }
            }
        }
    }

    void exibir(char s[],int tl,No no){
        if(no == null) return ;
        for(int j=0;j<no.getInfo().length();j++){
            s[tl++] = no.getInfo().charAt(j);
        }
        if(no.isTerminal()) {
            String s2="";
            for(int j=0;j<tl;j++){
                s2+=s[j];
            }
            System.out.println(s2);
            palavras.add(s2);
        }
        for(int i=0;i<26;i++){
            exibir(s,tl,no.getvLig(i));
        }
    }


    void exibir() {
        char s[] = new char[100];
        exibir(s,0,raiz);
    }

    public void exibeLevel() {
        Fila queue = new Fila();
        queue.push(raiz);

        while (!queue.isEmpty()) {
            No current = queue.pop();
            System.out.println(current.getInfo());

            for (int i=0;i<26;i++) {
                if (current.getvLig(i)!= null) {
                    queue.push(current.getvLig(i));
                }
            }
        }
    }
}
