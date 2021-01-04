using System;
using System.Collections.Generic;
using System.Text;
using Lab9_MAP.model;

namespace Lab9_MAP.validator
{
    class MeciValidator:IValidator<Meci>
    {
        public void Validate(Meci meci)
        {
            if(meci.ID == "")
                throw new ValidationException("ID-ul meciului nu poate fi vid!");
            if(meci.idEchipa1 == "")
                throw new ValidationException("ID-ul primei echipe nu poate fi vid!");
            if (meci.idEchipa2 == "")
                throw new ValidationException("ID-ul celei de-a doua echipe nu poate fi vid!");
            if(meci.data.ToString() == "")
                throw new ValidationException("Data meciului nu poate fi vida!");
        }
    }
}
