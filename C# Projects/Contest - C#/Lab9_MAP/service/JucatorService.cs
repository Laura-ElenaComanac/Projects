using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lab9_MAP.model;
using Lab9_MAP.repository;

namespace Lab9_MAP.service
{
    class JucatorService
    {
        private IRepository<string, Jucator> repoJucator;
        private IRepository<string, Echipa> repoEchipa;

        public JucatorService(IRepository<string,Jucator> repo, IRepository<string, Echipa> repoEchipa)
        {
            this.repoJucator = repo;
            this.repoEchipa = repoEchipa;
        }

        public List<Jucator> FindAllJucatori()
        {
            return repoJucator.FindAll().ToList();
        }

        public List<String> JucatoriEchipa(String NumeEchipa)
        {
           /* List<String> listaIDJucatori = new List<String>();
            String idEchipa = "0";

            List<Echipa> echipe = repoEchipa.FindAll().ToList();
            foreach (Echipa Echipa in echipe)
                if (Echipa.Nume == NumeEchipa)
                    idEchipa = Echipa.ID;

            foreach (Jucator jucator in FindAllJucatori())
                if (jucator.IdEchipa == idEchipa)
                    listaIDJucatori.Add(jucator.ID);*/

            List<Echipa> echipe = repoEchipa.FindAll().ToList();
            var idEchipa = from echipa in echipe.Where(e => e.Nume == NumeEchipa)
                           select echipa.ID;
            String IDEchipa = idEchipa.FirstOrDefault();

            var IDJucatori = from jucator in FindAllJucatori().Where(j => j.IdEchipa == IDEchipa)
                             select jucator.ID;
            List<String> listaIDJucatori = IDJucatori.ToList();

            return listaIDJucatori;
        }

        public List<String> JucatoriActiviIDMeciEchipa(String NumeEchipa, List<String> listaJucatoriActiviIDMeci)
        {
            /*List<String> listaJucatoriActiviIDEchipaMeci = new List<String>();

            foreach (String IDJucator in JucatoriEchipa(NumeEchipa))
                if (listaJucatoriActiviIDMeci.Contains(IDJucator))
                    listaJucatoriActiviIDEchipaMeci.Add(IDJucator);*/

            var jucatoriActiviIDEchipaMeci = from IDJucator in JucatoriEchipa(NumeEchipa).Where(s => listaJucatoriActiviIDMeci.Contains(s))
                                             select IDJucator;
            List<String> listaJucatoriActiviIDEchipaMeci = jucatoriActiviIDEchipaMeci.ToList();

            return listaJucatoriActiviIDEchipaMeci;
        }

        public Tuple<List<String>,List<String>> JucatoriEchipe(Tuple<String, String> echipe)
        {
            /*List<String> lista1 = new List<String>();
            List<String> lista2 = new List<String>();

            foreach (Jucator jucator in FindAllJucatori()) {
                if (jucator.IdEchipa == echipe.Item1)
                    lista1.Add(jucator.ID);
                if (jucator.IdEchipa == echipe.Item2)
                    lista2.Add(jucator.ID);
            }*/

            var l1 = from jucator in FindAllJucatori().Where(j => j.IdEchipa == echipe.Item1)
                     select jucator.ID;
            List<String> lista1 = l1.ToList();

            var l2 = from jucator in FindAllJucatori().Where(j => j.IdEchipa == echipe.Item2)
                     select jucator.ID;
            List<String> lista2 = l2.ToList();

            Tuple<List<String>, List<String>> jucatoriEchipe = new Tuple<List<String>, List<String>>(lista1, lista2);
            return jucatoriEchipe;
        }
    }
}
