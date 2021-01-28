package app.service;

import app.domain.Raspuns;
import app.domain.Rezultat;
import app.repository.Repository;
import app.utils.events.ChangeEventType;
import app.utils.events.RezultatChangeEvent;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

public class RezultatService extends Service<Integer, Rezultat, RezultatChangeEvent>{

    public RezultatService(Repository<Integer, Rezultat> repo) {
        super(repo);
    }

    @Override
    protected RezultatChangeEvent createNewEvent(ChangeEventType type, Rezultat rezultat) {
        return new RezultatChangeEvent(type, rezultat);
    }

    public List<Rezultat> calculeazaNote(List<Raspuns> raspunsuri)
    {
        List<Rezultat> note = new LinkedList<>();
        HashMap<String,Double> studentRaspunsuri = new HashMap<>();

        for(Raspuns raspuns : raspunsuri) {
            if(studentRaspunsuri.containsKey(raspuns.getNumeStudent())) {
                Double acumulat = studentRaspunsuri.get(raspuns.getNumeStudent());
                studentRaspunsuri.put(raspuns.getNumeStudent(), acumulat + raspuns.getPunctaj());
            }
            else
                studentRaspunsuri.put(raspuns.getNumeStudent(), raspuns.getPunctaj());
        }

        for(Map.Entry<String,Double> entry : studentRaspunsuri.entrySet())
            note.add(new Rezultat(entry.getKey(), entry.getValue()));
        return note;
    }
}
