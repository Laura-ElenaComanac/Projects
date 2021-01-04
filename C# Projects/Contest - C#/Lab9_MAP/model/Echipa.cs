using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab9_MAP.model
{
    class Echipa : Entity<String>
    {
        public String Nume{ get; set;}

        public override string ToString()
        {
            return Nume;
        }
    }
}
