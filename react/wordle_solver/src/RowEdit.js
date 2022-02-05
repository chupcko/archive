import { useContext } from 'react';

import { Stack, Button, Box, Typography } from '@mui/material';

import { StoreContext } from './Store';

const RowEdit = (props) => {

  const { game, change, next, done } = useContext(StoreContext);

  return (
    <Stack direction="row" spacing={ 1 }>
      {
        game.rows[props.index].map(
          (field, index) => <Button
            variant="outlined"
            key={ index }
            onClick={ () => { change(index); } }
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
      <Button variant="contained" onClick={ next } >
        Next
      </Button>
      <Button variant="contained" onClick={ done } >
        Got It
      </Button>
      <Box
        display="flex"
        justifyContent="center"
        alignItems="center"
      >
        <Typography>({ game.words.length })</Typography>
      </Box>
    </Stack>
  );

};

export default RowEdit;
