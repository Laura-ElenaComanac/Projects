using Lab9_MAP.model;
using System;
using System.Collections.Generic;
using System.Text;

namespace Lab9_MAP.validator
{
    class JucatorValidator:IValidator<Jucator>
    {
        public void Validate(Jucator jucator)
        {
            if(jucator.IdEchipa == "")
                throw new ValidationException("Id-ul echipei nu poate fi vid!");
            if (jucator.ID == "")
                throw new ValidationException("Id-ul jucatorului nu poate fi vid!");
        }
    }
}
