package app.domain;

import java.util.Objects;
import java.util.concurrent.atomic.AtomicInteger;

public class Raspuns extends Entity<Integer>{
    private Integer nrIntrebare;
    private String numeStudent;
    private Double punctaj;

    static AtomicInteger identity = new AtomicInteger(0);

    public Raspuns(Integer nrIntrebare, String numeStudent, Double punctaj) {
        this.nrIntrebare = nrIntrebare;
        this.numeStudent = numeStudent;
        this.punctaj = punctaj;

        this.setId(identity.incrementAndGet());
    }

    public Integer getNrIntrebare() {
        return nrIntrebare;
    }

    public void setNrIntrebare(Integer nrIntrebare) {
        this.nrIntrebare = nrIntrebare;
    }

    public String getNumeStudent() {
        return numeStudent;
    }

    public void setNumeStudent(String numeStudent) {
        this.numeStudent = numeStudent;
    }

    public Double getPunctaj() {
        return punctaj;
    }

    public void setPunctaj(Double punctaj) {
        this.punctaj = punctaj;
    }

    @Override
    public boolean equals(Object obj) {
        if(this == obj)
            return true;
        if(!(obj instanceof Raspuns))
            return false;
        Raspuns raspuns = (Raspuns) obj;
        return Objects.equals(getNrIntrebare(), raspuns.getNrIntrebare()) &&
                Objects.equals(getNumeStudent(), raspuns.getNumeStudent()) &&
                Objects.equals(getPunctaj(), raspuns.getPunctaj());
    }

}
