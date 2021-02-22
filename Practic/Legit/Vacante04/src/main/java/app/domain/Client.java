package app.domain;

import java.util.Objects;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicLong;

public class Client extends Entity<Long> {
    String name;
    Integer fidelityGrade;
    Integer varsta;
    public enum hobby{reading, music, hiking, walking, extreme_sports};
    hobby hobby;


    public Client(Long id, String name, Integer fidelityGrade, Integer varsta, hobby hobby) {
        this.name = name;
        this.fidelityGrade = fidelityGrade;
        this.varsta = varsta;
        this.hobby = hobby;

        setId(id);
    }

    public Client.hobby getHobby() {
        return hobby;
    }

    public void setHobby(Client.hobby hobby) {
        this.hobby = hobby;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Integer getFidelityGrade() {
        return fidelityGrade;
    }

    public void setFidelityGrade(Integer fidelityGrade) {
        this.fidelityGrade = fidelityGrade;
    }

    public Integer getVarsta() {
        return varsta;
    }

    public void setVarsta(Integer varsta) {
        this.varsta = varsta;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Client client = (Client) o;
        return this.getId().equals(client.getId()) && name.equals(client.name) && fidelityGrade.equals(client.fidelityGrade) && varsta.equals(client.varsta);
    }

    @Override
    public int hashCode() {
        return Objects.hash(this.getId(), name, fidelityGrade, varsta);
    }
}
