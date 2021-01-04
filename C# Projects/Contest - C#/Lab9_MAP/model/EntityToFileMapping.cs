using System;
using System.Collections.Generic;
using System.Text;

namespace Lab9_MAP.model
{
    class EntityToFileMapping
    {
        public static Echipa CreateEchipa(string line)
        {
            string[] fields = line.Split(',');
            Echipa echipa = new Echipa() {
                ID = fields[0],
                Nume = fields[1]
            };
            return echipa;
        }
        public static Elev CreateElev(string line)
        {
            string[] fields = line.Split(',');
            Elev elev = new Elev() {
                ID = fields[0],
                Nume = fields[1],
                Scoala = fields[2]
            };
            return elev;
        }
        public static Jucator CreateJucator(string line)
        {
            string[] fields = line.Split(',');
            Jucator jucator = new Jucator() {
                IdEchipa = fields[0],
                ID = fields[1],
            };
            return jucator;
        }
        public static Meci CreateMeci(string line)
        {
            string[] fields = line.Split(',');
            Meci meci = new Meci() {
                ID = fields[0],
                idEchipa1 = fields[1],
                idEchipa2 = fields[2],
                data = DateTime.Parse(fields[3])
            };
            return meci;
        }
        public static JucatorActiv CreateJucatorActiv(string line)
        {
            string[] fields = line.Split(',');
            JucatorActiv jucatorActiv = new JucatorActiv() {
                ID = fields[0],
                IdMeci = fields[1],
                NrPuncteInscrise = int.Parse(fields[2]),
                Tip = (Tip)Enum.Parse(typeof(Tip), fields[3])
            };
            return jucatorActiv;
        }
    }
}
