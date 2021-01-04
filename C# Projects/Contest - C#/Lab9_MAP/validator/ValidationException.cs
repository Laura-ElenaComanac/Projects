using System;
using System.Collections.Generic;
using System.Text;

namespace Lab9_MAP.validator
{
    class ValidationException: ApplicationException
    {
        public ValidationException(String message): base(message) { }
    }
}
