using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lab9_MAP.model;
using Lab9_MAP.repository;

namespace Lab9_MAP.service
{
    class EchipaService
    {
        private IRepository<string, Echipa> repoEchipa;

        public EchipaService(IRepository<string,Echipa> repo)
        {
            this.repoEchipa = repo;
        }

        public List<Echipa> FindAllEchipe()
        {
            return repoEchipa.FindAll().ToList();
        }

        public String IDToNume(String ID)
        {
            /*String nume = "";

            foreach (Echipa echipa in FindAllEchipe())
                if (echipa.ID == ID)
                    nume = echipa.Nume;*/

            var numele = from echipa in FindAllEchipe().Where(e => e.ID == ID)
                         select echipa.Nume;

            return numele.FirstOrDefault();
        }

    }
}
