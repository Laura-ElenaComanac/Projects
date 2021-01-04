using System;
using System.Collections.Generic;
using System.Text;
using Lab9_MAP.model;

namespace Lab9_MAP.validator
{
    class JucatorActivValidator : IValidator<JucatorActiv>
    {
        public void Validate(JucatorActiv jucatorActiv)
        {
            if (jucatorActiv.ID == "")
                throw new ValidationException("Id-ul jucatorului nu poate fi vid!");
            if (jucatorActiv.IdMeci == "")
                throw new ValidationException("Id-ul meciului nu poate fi vid!");
            if (jucatorActiv.NrPuncteInscrise < 0)
                throw new ValidationException("Numarul de puncte inscrise nu poate fi negativ!");
        }
    }
}
