using System;
using System.Collections.Generic;
using System.Text;
using Lab9_MAP.model;

namespace Lab9_MAP.validator
{
    class ElevValidator:IValidator<Elev>
    {
        public void Validate(Elev elev)
        {
            if (elev.Nume == "")
                throw new ValidationException("Numele elevului nu poate fi vid!");
            if (elev.Scoala == "")
                throw new ValidationException("Scoala elevului nu poate fi vida!");
        }
    }
}
