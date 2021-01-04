using System;
using System.Collections.Generic;
using System.Text;
using Lab9_MAP.model;
using Lab9_MAP.validator;

namespace Lab9_MAP.repository
{
    class MeciInFileRepository:InFileRepository<string,Meci>
    {
        public MeciInFileRepository(IValidator<Meci> validator, string filename) : base(validator, filename, EntityToFileMapping.CreateMeci) { }
    }
}
