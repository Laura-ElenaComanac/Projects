using System;
using System.Collections.Generic;
using System.Text;

namespace Lab9_MAP.model
{
    enum Tip
    {
        Rezerva, Participant
    }
    class JucatorActiv : Jucator
    {
        public String IdMeci { get; set; }
        public int NrPuncteInscrise { get; set; }
        public Tip Tip { get; set; }

        public override string ToString()
        {
            return base.ID + "," + IdMeci + "," + NrPuncteInscrise + "," + Tip;
        }
    }
}
