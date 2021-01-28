package app.domain;


import java.util.Objects;
import java.util.concurrent.atomic.AtomicInteger;

public class Intrebare extends Entity<Integer> {
    private Integer nrIntrebare;
    private String descriere;
    private String v1;
    private String v2;
    private String v3;
    private String raspunsCorect;
    private Double punctaj;

    static AtomicInteger identity = new AtomicInteger(0);

    public Intrebare(Integer nrIntrebare, String descriere, String v1, String v2, String v3, String raspunsCorect, Double punctaj) {
        this.nrIntrebare = nrIntrebare;
        this.descriere = descriere;
        this.v1 = v1;
        this.v2 = v2;
        this.v3 = v3;
        this.raspunsCorect = raspunsCorect;
        this.punctaj = punctaj;

        this.setId(identity.incrementAndGet());
    }

    public Integer getNrIntrebare() {
        return nrIntrebare;
    }

    public void setNrIntrebare(Integer nrIntrebare) {
        this.nrIntrebare = nrIntrebare;
    }

    public String getDescriere() {
        return descriere;
    }

    public void setDescriere(String descriere) {
        this.descriere = descriere;
    }

    public String getV1() {
        return v1;
    }

    public void setV1(String v1) {
        this.v1 = v1;
    }

    public String getV2() {
        return v2;
    }

    public void setV2(String v2) {
        this.v2 = v2;
    }

    public String getV3() {
        return v3;
    }

    public void setV3(String v3) {
        this.v3 = v3;
    }

    public Double getPunctaj() {
        return punctaj;
    }

    public void setPunctaj(Double punctaj) {
        this.punctaj = punctaj;
    }

    public String getRaspunsCorect() {
        return raspunsCorect;
    }

    public void setRaspunsCorect(String raspunsCorect) {
        this.raspunsCorect = raspunsCorect;
    }

    @Override
    public boolean equals(Object obj) {
        if(this == obj)
            return true;
        if(!(obj instanceof Intrebare))
            return false;
        Intrebare intrebare = (Intrebare) obj;
        return Objects.equals(getNrIntrebare(), intrebare.getNrIntrebare()) &&
                Objects.equals(getDescriere(), intrebare.getDescriere()) &&
                Objects.equals(getV1(), intrebare.getV1()) &&
                Objects.equals(getV2(), intrebare.getV2()) &&
                Objects.equals(getV3(), intrebare.getV3()) &&
                Objects.equals(getPunctaj(), intrebare.getPunctaj()) &&
                Objects.equals(getRaspunsCorect(), intrebare.getRaspunsCorect());
    }
}
