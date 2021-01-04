using Lab9_MAP.model;
using System;
using System.Collections.Generic;
using System.Text;

namespace Lab9_MAP.validator
{
    class EchipaValidator:IValidator<Echipa>
    {
        public void Validate(Echipa echipa)
        {
            if (echipa.Nume == "")
                throw new ValidationException("Numele echipei nu poate fi vid!");
        }
    }
}
