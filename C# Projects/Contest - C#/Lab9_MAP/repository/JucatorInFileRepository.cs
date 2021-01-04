using System;
using System.Collections.Generic;
using System.Text;
using Lab9_MAP.model;
using Lab9_MAP.validator;

namespace Lab9_MAP.repository
{
    class JucatorInFileRepository:InFileRepository<string,Jucator>
    {
        public JucatorInFileRepository(IValidator<Jucator> validator, string filename) : base(validator, filename, EntityToFileMapping.CreateJucator) { }
    }
}
