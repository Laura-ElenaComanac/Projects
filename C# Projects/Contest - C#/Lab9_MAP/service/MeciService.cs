using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Lab9_MAP.model;
using Lab9_MAP.repository;

namespace Lab9_MAP.service
{
    class MeciService
    {
        private IRepository<string, Meci> repoMeci;

        public MeciService(IRepository<string,Meci> repo)
        {
            this.repoMeci = repo;
        }

        public List<Meci> FindAllMeciuri()
        {
            return repoMeci.FindAll().ToList();
        }

        public List<Meci> MeciuriPerioada(DateTime data1, DateTime data2)
        {
            List<Meci> meciuri = new List<Meci>();

            foreach (Meci meci in FindAllMeciuri())
                if (DateTime.Compare(data1, meci.data) <= 0 && DateTime.Compare(meci.data, data2) <= 0)
                    meciuri.Add(meci);

            return meciuri;
        }

        public Tuple<String,String> EchipeMeci(String idMeci)
        {
            Tuple<String, String> echipe = new Tuple<String, String>("","");

            foreach (Meci meci in FindAllMeciuri())
                if (meci.ID == idMeci)
                    echipe = Tuple.Create(meci.idEchipa1, meci.idEchipa2);

            return echipe;
        }
    }
}
