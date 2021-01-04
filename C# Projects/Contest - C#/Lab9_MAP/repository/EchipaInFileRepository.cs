using System;
using System.Collections.Generic;
using System.Text;
using Lab9_MAP.model;
using Lab9_MAP.validator;

namespace Lab9_MAP.repository
{
    class EchipaInFileRepository:InFileRepository<string,Echipa>
    {
        public EchipaInFileRepository(IValidator<Echipa> validator, string filename) : base(validator, filename, EntityToFileMapping.CreateEchipa) { }
    }
}
