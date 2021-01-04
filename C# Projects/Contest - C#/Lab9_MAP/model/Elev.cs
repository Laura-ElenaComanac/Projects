using System;
using System.Collections.Generic;
using System.Text;

namespace Lab9_MAP.model
{
    class Elev : Entity<String>
    {
        public String Nume { get; set; }
        public String Scoala { get; set; }

        public override string ToString()
        {
            return  Nume + "," + Scoala;
        }
    }
}
