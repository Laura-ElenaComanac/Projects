using System;
using System.Collections.Generic;
using System.Text;

namespace Lab9_MAP.model
{
    class Jucator : Elev
    {
        public String IdEchipa { get; set; }

        public override string ToString()
        {
            return IdEchipa + "," + base.ID + "," + base.Nume;
        }
    }
}
