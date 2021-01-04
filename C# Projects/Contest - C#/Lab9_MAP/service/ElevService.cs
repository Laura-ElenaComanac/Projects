using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lab9_MAP.model;
using Lab9_MAP.repository;

namespace Lab9_MAP.service
{
    class ElevService
    {
        private IRepository<string, Elev> repoElev;

        public ElevService(IRepository<string,Elev> repo)
        {
            this.repoElev = repo;
        }

        public List<Elev> FindAllElevi()
        {
            return repoElev.FindAll().ToList();
        }

        public List<String> EleviID(List<String> ids)
        {
            /*List<String> listaNume = new List<String>();

            foreach (String id in ids)
                foreach (Elev elev in FindAllElevi())
                    if (id == elev.ID)
                        listaNume.Add(elev.Nume);*/

            var listNumelor = from id in ids
                              from elev in FindAllElevi().Where(e => e.ID == id)
                              select elev.Nume;
            List<String> nume = listNumelor.ToList();

            return nume;
        }
    }
}
