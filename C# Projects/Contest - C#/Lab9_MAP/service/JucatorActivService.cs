using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lab9_MAP.model;
using Lab9_MAP.repository;

namespace Lab9_MAP.service
{
    class JucatorActivService
    {
        private IRepository<string, JucatorActiv> repoJucatorActiv;

        public JucatorActivService(IRepository<string, JucatorActiv> repo)
        {
            this.repoJucatorActiv = repo;
        }

        public List<JucatorActiv> FindAllJucatoriActivi()
        {
            return repoJucatorActiv.FindAll().ToList();
        }

        public List<String> JucatoriActiviIDMeci(String idMeci)
        {
            /*List<String> listaJucatoriActiviIDMeci = new List<String>();

            foreach (JucatorActiv jucatorActiv in FindAllJucatoriActivi())
                if (jucatorActiv.IdMeci == idMeci)
                    listaJucatoriActiviIDMeci.Add(jucatorActiv.ID);*/

            var jucatoriActiviIDMeci = from jucatorActiv in FindAllJucatoriActivi().Where(ja => ja.IdMeci == idMeci)
                                       select jucatorActiv.ID;
            List<String> listaJucatoriActiviIDMeci = jucatoriActiviIDMeci.ToList();

            return listaJucatoriActiviIDMeci;
        }

        public Tuple<int, int> ScorEchipe(Tuple<List<String>, List<String>> jucatoriEchipe)
        {
            /*List<String> echipa1 = jucatoriEchipe.Item1;
            List<String> echipa2 = jucatoriEchipe.Item2;
            int nrPuncte1 = 0;
            int nrPuncte2 = 0;

            foreach (JucatorActiv jucatorActiv in FindAllJucatoriActivi()) {
                if (echipa1.Contains(jucatorActiv.ID))
                    nrPuncte1 += jucatorActiv.NrPuncteInscrise;
                if (echipa2.Contains(jucatorActiv.ID))
                    nrPuncte2 += jucatorActiv.NrPuncteInscrise;
            }*/

            List<String> echipa1 = jucatoriEchipe.Item1;
            List<String> echipa2 = jucatoriEchipe.Item2;

            var np1 = from jucatorActiv in FindAllJucatoriActivi().Where(ja => echipa1.Contains(ja.ID))
                      select jucatorActiv.NrPuncteInscrise;

            var np2 = from jucatorActiv in FindAllJucatoriActivi().Where(ja => echipa2.Contains(ja.ID))
                      select jucatorActiv.NrPuncteInscrise;

            int nrPuncte1 = np1.Sum();
            int nrPuncte2 = np2.Sum();

            Tuple<int, int> scor = new Tuple<int, int>(nrPuncte1, nrPuncte2);
            return scor;
        }
    }
}
