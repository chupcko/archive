import { useContext } from 'react';

import { Stack, Button } from '@mui/material';

import { StoreContext } from './Store';

const RowShow = (props) => {

  const { game } = useContext(StoreContext);

  return (
    <Stack direction="row" spacing={ 1 }>
      {
        game.rows[props.index].map(
          (field, index) => <Button
            variant="outlined"
            disabled
            key={ index }
            style={ {
              backgroundColor: game.rows[props.index][index].color,
              minWidth: '2em',
              maxWidth: '2em'
            } }
          >
            <b>{ game.rows[props.index][index].letter }</b>
          </Button>
        )
      }
    </Stack>
  );

};

export default RowShow;
