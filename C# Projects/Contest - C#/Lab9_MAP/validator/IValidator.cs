using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab9_MAP.validator
{
    interface IValidator<E>
    {
        void Validate(E e);
    }
}
