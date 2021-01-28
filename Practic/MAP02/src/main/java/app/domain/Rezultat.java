package app.domain;

import java.util.Objects;
import java.util.concurrent.atomic.AtomicInteger;

public class Rezultat extends Entity<Integer>{
    private String numeStudent;
    private Double nota;

    static AtomicInteger identity = new AtomicInteger(0);

    public Rezultat(String numeStudent, Double nota) {
        this.numeStudent = numeStudent;
        this.nota = nota;

        this.setId(identity.incrementAndGet());
    }

    public String getNumeStudent() {
        return numeStudent;
    }

    public Double getNota() {
        return nota;
    }

    public void setNumeStudent(String numeStudent) {
        this.numeStudent = numeStudent;
    }

    public void setNota(Double nota) {
        this.nota = nota;
    }

    @Override
    public boolean equals(Object obj) {
        if(this == obj)
            return true;
        if(!(obj instanceof Rezultat))
            return false;
        Rezultat rezultat = (Rezultat) obj;
        return Objects.equals(getNumeStudent(), rezultat.getNumeStudent()) &&
                Objects.equals(getNota(), rezultat.getNota());
    }

}
