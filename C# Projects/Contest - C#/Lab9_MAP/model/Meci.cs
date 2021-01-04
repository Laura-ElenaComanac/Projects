using System;
using System.Collections.Generic;
using System.Text;

namespace Lab9_MAP.model
{
    class Meci : Entity<String>
    {
        public String idEchipa1 { get; set; }
        public String idEchipa2 { get; set; }
        public DateTime data { get; set; }

        public override string ToString()
        {
            return ID + "," + idEchipa1 + "," + idEchipa2 + "," + data;
        }
    }
}
